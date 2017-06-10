
#ifndef __DICTIONARYHELPER_H__
#define __DICTIONARYHELPER_H__

#include "../rapidjson/include/document.h"
#include <string>
using namespace std;

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define CC_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define CC_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define CC_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define CC_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)
#define CC_BREAK_IF(cond)           if(cond) break

typedef enum
{
	JsonNull = 0,
	JsonFalse,
	JsonTrue,
	JsonObject,
	JsonArray,
	JsonString,
	JsonNumbe,
} jsonValueType;


#define DICTOOL DictionaryHelper::getInstance()


class  DictionaryHelper
{
public:
    DictionaryHelper();
    ~DictionaryHelper();
    static DictionaryHelper* getInstance();
	static void destroyInstance();
    
	const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key);
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx);
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, int idx);
    
	int   getIntValue_json(const rapidjson::Value& root, const char* key, int def = 0);
	float getFloatValue_json(const rapidjson::Value& root,const char* key, float def = 0.0f);
    bool  getBooleanValue_json(const rapidjson::Value& root,const char* key, bool def = false);
    const char* getStringValue_json(const rapidjson::Value& root,const char* key, const char *def = NULL);
    int   getArrayCount_json(const rapidjson::Value& root,const char* key, int def = 0);
	
    int   getIntValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, int def = 0);
	float getFloatValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, float def = 0.0f);
	bool  getBoolValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, bool def = false);
	const char* getStringValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, const char *def = NULL);
	const rapidjson::Value &getDictionaryFromArray_json(const rapidjson::Value &root, const char* key,int idx);
	bool checkObjectExist_json(const rapidjson::Value &root);
    bool checkObjectExist_json(const rapidjson::Value &root, const char* key);
    bool checkObjectExist_json(const rapidjson::Value &root, int index);
	const char* getValue_json(const rapidjson::Value& root, const char* key, const char *def = NULL);

private:
	string m_Result;
};


#endif /* defined(__CocoGUI__DictionaryHelper__) */
