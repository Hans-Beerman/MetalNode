#ifdef ESP32

#include <Cache.h>
#include <string.h>
#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include "ACNode-private.h"

// #define DEBUG_CACHE

#define CACHE_DIR_PREFIX "/tags"
#define TAG_FILE_PREFIX "/tag"

#define MAX_CACHE_DEPTH 100

#define UPDATE_TO_SPIFFS_INTERVAL 24 * 3600 // 1 day in beatcount seconds
//#define UPDATE_TO_SPIFFS_INTERVAL 60 // for test 60 s

unsigned long cacheMiss = 0;
unsigned long cacheHit = 0;

struct validtag {
  unsigned long uidHash;
  unsigned long lastSeen;
  unsigned int count;
  bool backupMadeInSpiffs;
};

static unsigned long nextUpdateSPIFFSCheck = 0;

static struct validtag tagCache[MAX_CACHE_DEPTH];

static int tagsInCache;

static int SPIFFSCounter = 0;

unsigned long hash(const char * tag) {
  int len = strlen(tag);
  unsigned long hash = 5381;
  int i = 0;

   for (i = 0; i < len; ++tag, ++i)
   {
      hash = ((hash << 5) + hash) + (*tag);
   }

   return hash;
}

int findTag(const char * tag) {
  unsigned long currentHash = hash(tag);
  for (int i = 0; i < MAX_CACHE_DEPTH; i++) {
    if (tagCache[i].count > 0) {
      if (currentHash == tagCache[i].uidHash) {
#ifdef DEBUG_CACHE        
        Debug.print("Tag found in cache[i], i = ");
        Debug.print(i);
        Debug.print(" tag = ");
        Debug.println(tag);
        Debug.print(" count = ");
        Debug.println(tagCache[i].count);
#endif        
        return i;
      }
    }
  }
#ifdef DEBUG_CACHE        
  Debug.print("Tag not found in cache: ");
  Debug.println(tag);
#endif
  return -1;
}

void prepareCache(bool wipe) {
  Log.println(wipe ? "Resetting cache" : "Cache preparing.");
  if (!SPIFFS.begin()) {
    Log.println("Mount failed - trying to reformat");
    if (!SPIFFS.format() || !SPIFFS.begin()) {
      Log.println("SPIFFS mount after re-formatting also failed. Giving up. No caching.");
      return;
    };
  };

  if (wipe) {
    for (int i = 0; i < MAX_CACHE_DEPTH; i++) {
      tagCache[i].count = 0;
    }
    tagsInCache = 0;
    Log.println("RAM Cache cleared");  

    // remove al tag entries from SPIFFS
    String dirName = CACHE_DIR_PREFIX;
    if (!SPIFFS.exists(dirName)) { 
    	SPIFFS.mkdir(dirName);
    }
    File dir = SPIFFS.open(dirName);
    File file = dir.openNextFile();
    while(file) {
      String path = file.name();
      file.close();
      SPIFFS.remove(path);
#ifdef DEBUG_CACHE        
      Debug.print("Removed from SPIFFS: ");
      Debug.println(path);
#endif
      dir.close();
      dir = SPIFFS.open(dirName);
      file = dir.openNextFile();
    };
    dir.close();
    Log.println("Back-up of cache in SPIFFS cleared");  
  } else {
    // restore the cache from the back-up in SPIFFS
    String path;
    File tagFile;
    int readSize = 0;
  
    tagsInCache = 0;
    for (int i = 0; i < MAX_CACHE_DEPTH; i++) {
      path = CACHE_DIR_PREFIX + (String)TAG_FILE_PREFIX + String(i, DEC);
      if (SPIFFS.exists(path)) {
        tagFile = SPIFFS.open(path, "rb");
        tagFile.setTimeout(0);
        readSize = tagFile.readBytes((char*)&tagCache[i], sizeof(tagCache[i]));
        if (readSize == sizeof(tagCache[i])) {
          tagCache[i].backupMadeInSpiffs = true;
          tagsInCache++;
#ifdef DEBUG_CACHE        
          Debug.print("From SPIFFS to cache in Ram, tagCache[i], i = ");  
          Debug.print(i);  
          Debug.print(" count = ");  
          Debug.println(tagCache[i].count);  
#endif
        }
        tagFile.close();
      } else {
        tagCache[i].count = 0;
#ifdef DEBUG_CACHE        
        Debug.print("No entry in SPIFFS for tagCache[i], i = ");  
        Debug.println(i);  
#endif
      }
    }
    Log.print("Total nr. of tags restored from back-up in SPIFFS = ");  
    Log.println(tagsInCache);  
  }

  Log.println("Cache ready.");
};

void setCache(const char * tag, bool ok, unsigned long beatCounter) {
  int oldestEntryInCache;
  int posInCache = findTag(tag);
  int entryInCache = -1;
  
  if (ok) { // add to cache, or update in cache
    if (posInCache >= 0) { // tag is already cached
      tagCache[posInCache].count++;
      tagCache[posInCache].lastSeen = beatCounter;
      tagCache[posInCache].backupMadeInSpiffs = false; // change to true after update to SPIFFS
      entryInCache = posInCache;
#ifdef DEBUG_CACHE        
      Debug.print("Update entry in cache[i] i = ");
      Debug.print(posInCache);
      Debug.print(" tag = ");
      Debug.print(tag);
      Debug.print(" count = ");
      Debug.print(tagCache[entryInCache].count);
      Debug.print(" nr of tags in cache = ");
      Debug.println(tagsInCache);
#endif
    } else { // tag is new 
      if (tagsInCache < MAX_CACHE_DEPTH) { // there is enough room in cache, so search for first empty place
        for (int i = 0; i < MAX_CACHE_DEPTH; i++) {
          if (tagCache[i].count == 0) { // count == 0: this is an empty place
            tagCache[i].uidHash = hash(tag);
            tagCache[i].count = 1;
            tagCache[i].lastSeen = beatCounter;
            tagCache[i].backupMadeInSpiffs = false; // change to true after update to SPIFFS
            entryInCache = i;
            tagsInCache++; // increment number of tags stored in cache
#ifdef DEBUG_CACHE        
            Debug.print("Added new tag to empty place in cache[i] i = ");
            Debug.print(entryInCache);
            Debug.print(" tag = ");
            Debug.print(tag);
            Debug.print(" count = ");
            Debug.print(tagCache[entryInCache].count);
            Debug.print(" nr of tags in cache = ");
            Debug.println(tagsInCache);
#endif
            break;
          }
        }
      } else { // cache is full so replace oldest entry in cache with new tag info
        oldestEntryInCache = 0; // start with first entry
        for (int i = 1; i < MAX_CACHE_DEPTH; i++) {
          if (tagCache[i].lastSeen < tagCache[oldestEntryInCache].lastSeen) { // if < then this one is older
            oldestEntryInCache = i;
          }
        }
        tagCache[oldestEntryInCache].uidHash = hash(tag); // store the hash from the new tag
        tagCache[oldestEntryInCache].count = 1;
        tagCache[oldestEntryInCache].lastSeen = beatCounter;
        tagCache[oldestEntryInCache].backupMadeInSpiffs = false; // change to true after update to SPIFFS
        entryInCache = oldestEntryInCache;
#ifdef DEBUG_CACHE        
        Debug.print("Cache is full new tag stored in tagCache[i], containing oldest entry i = ");
        Debug.print(entryInCache);
        Debug.print(" tag = ");
        Debug.print(tag);
        Debug.print(" count = ");
        Debug.print(tagCache[entryInCache].count);
        Debug.print(" nr of tags in cache = ");
        Debug.println(tagsInCache);
#endif
      }
      // back-up this new tag to SPIFFS
      if (entryInCache >= 0) {
        String path = CACHE_DIR_PREFIX + (String)TAG_FILE_PREFIX + String(entryInCache, DEC);
        File tagFile;
        unsigned int writeSize;
        tagCache[entryInCache].backupMadeInSpiffs = true;
        tagFile = SPIFFS.open(path, "wb");
        writeSize = tagFile.write((byte*)&tagCache[entryInCache], sizeof(tagCache[entryInCache]));
        if (writeSize != sizeof(tagCache[entryInCache]))
        {
          tagCache[entryInCache].backupMadeInSpiffs = false;
#ifdef DEBUG_CACHE        
          Debug.print("ERROR --> Tag: ");
          Debug.print(tag);
          Debug.println("NOT stored in SPIFFS");
#endif
        }
        else
        {
#ifdef DEBUG_CACHE        
          Debug.print("Tag: ");
          Debug.print(tag);
          Debug.println(" stored in SPIFFS");
#endif
        }
        
        tagFile.close();
      }
    }
  } else { // delete tag from cache (if stored)
    if (posInCache >= 0) { // tag is stored in cache
      tagCache[posInCache].count = 0; // disable tag in cache
#ifdef DEBUG_CACHE        
      Debug.print("Tag: ");
      Debug.print(tag);
      Debug.println(" removed from cache in RAM");
#endif

      String path = CACHE_DIR_PREFIX + (String)TAG_FILE_PREFIX + String(posInCache, DEC);
      if (SPIFFS.exists(path)) {
        SPIFFS.remove(path);
#ifdef DEBUG_CACHE        
        Debug.print("Tag: ");
        Debug.print(tag);
        Debug.println(" removed from SPIFFS");
#endif
      }
      
      if (tagsInCache > 0) { // one tag less in cache
        tagsInCache--;
      }
#ifdef DEBUG_CACHE        
      Debug.print("Nr. of tags in cache: ");
      Debug.println(tagsInCache);
#endif
    }
  }
}

bool checkCache(const char * tag) {
  int PosInCache = findTag(tag);
  if (PosInCache >= 0) {
    cacheHit++;
    return true;
  } else {
    cacheMiss++;
    return false;
  }
};

void cacheToSPIFFSLoop(unsigned long beatCounter) {
  if (beatCounter >= nextUpdateSPIFFSCheck) {
    if ((tagCache[SPIFFSCounter].count > 0) && (tagCache[SPIFFSCounter].backupMadeInSpiffs == false)) {
      String path = CACHE_DIR_PREFIX + (String)TAG_FILE_PREFIX + String(SPIFFSCounter, DEC);
      File tagFile;
      unsigned int writeSize;
      tagCache[SPIFFSCounter].backupMadeInSpiffs = true;
      tagFile = SPIFFS.open(path, "wb");
      writeSize = tagFile.write((byte*)&tagCache[SPIFFSCounter], sizeof(tagCache[SPIFFSCounter]));
      if (writeSize != sizeof(tagCache[SPIFFSCounter]))
      {
        tagCache[SPIFFSCounter].backupMadeInSpiffs = false;
#ifdef DEBUG_CACHE        
        Debug.print("ERROR --> Tag with hash: ");
        Debug.print(tagCache[SPIFFSCounter].uidHash);
        Debug.println("NOT stored in SPIFFS");
#endif
      }
      else
      {
#ifdef DEBUG_CACHE        
        Debug.print("Tag with hash: ");
        Debug.print(tagCache[SPIFFSCounter].uidHash);
        Debug.println(" stored in SPIFFS");
#endif
      }
      tagFile.close();
    }
    SPIFFSCounter++;
    if (SPIFFSCounter >= MAX_CACHE_DEPTH) {
      SPIFFSCounter = 0;
      nextUpdateSPIFFSCheck = beatCounter + UPDATE_TO_SPIFFS_INTERVAL;
    }
  }
}


#else
void prepareCache(bool wipe) { return; }
void setCache(const char * tag, bool ok, unsigned long beatCounter) { return; };
bool checkCache(const char * tag) { return false; };
#endif
