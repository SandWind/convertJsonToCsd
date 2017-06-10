#pragma once
#include <string>
#include <map>
#include <vector>
#include "../cfg/Config.h"

using namespace std;
using namespace cfg;

typedef struct
{
	vector<string> attributes;
	vector<string> properties;
}ObejectDetail;


class ObjectCfg
{
public:
	ObjectCfg(string CfgFilePath);
	~ObjectCfg();
	vector<string> getAttributeByName(const string &Name);
	vector<string> getPropertyByName(const string &Name);
	ObejectDetail* getDetailByName(const string &Name);
private:
	Config m_config;
	map<string, ObejectDetail>  m_Content;
	
	vector<string> m_sections;
	void LoadSection();
	void LoadContent();
	vector<string> split(string& s, string& delim);
};

