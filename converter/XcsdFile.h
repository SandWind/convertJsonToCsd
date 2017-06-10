#pragma once
#include "../tinyxml2/include/tinyxml2.h"
#include "../rapidjson/include/document.h"
#include "ObjectCfg.h"
#ifdef _DEBUG
	#pragma comment(lib, "../tinyxml2/lib/tinyxml2d.lib")
#else
	#pragma comment(lib, "/tinyxml2/lib/tinyxml2.lib")
#endif
using namespace rapidjson;
using namespace tinyxml2;
using namespace std;




class XcsdFile
{
public:
	XcsdFile();
	XcsdFile(string FilePath);
	XcsdFile(string FilePath,string CfgFilePath);
	~XcsdFile();
	void BeginCsd();
	void EndCsd();
	void WritePropertyGroup(const Value& value);
	void WriteContent(const Value &value);
private:
	void WriteInerContent(XMLElement *parent, const Value &value);
	void WriteObject(XMLElement *parent, const Value &Value);
	void WriteObjectForChildren(XMLElement *XmlSize, const Value& children);
	void WriteSingleJsonObject(XMLElement *parent, const Value& child);

	void WriteObjectAttribute(XMLElement *XmlNodeData, const Value& child, ObejectDetail *detail);

	void WriteObjectProperty(XMLElement *XmlProperty, const Value& Property, ObejectDetail *detail);

	void WriteDefaultProperty(XMLElement *XmlNodeData, const Value& child, string Name);

	tinyxml2::XMLDocument *m_pDoc;
	tinyxml2::XMLElement *m_Root;
	string m_filePath;
	ObjectCfg *m_pConfig;
};

