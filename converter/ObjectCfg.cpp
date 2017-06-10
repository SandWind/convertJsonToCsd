#include "ObjectCfg.h"



ObjectCfg::ObjectCfg(string CfgFilePath)
{
	if (CfgFilePath.length() > 0)
	{
		m_config.load(CfgFilePath);
		m_sections.clear();
		LoadSection();
		LoadContent();
	}
}


ObjectCfg::~ObjectCfg()
{
	m_sections.clear();
	m_Content.clear();
}


vector<string > ObjectCfg::split(string& s,string& delim)
{
	vector<string > ret;
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last>0)
	{
		ret.push_back(s.substr(last, index - last));
	}


	return ret;
}

void  ObjectCfg::LoadSection()
{
	string sections = m_config.get_value("Sections", "List");
	string delim(",");
	m_sections = split(sections, delim);
}

void  ObjectCfg::LoadContent()
{
	for (int i = 0; i < m_sections.size(); i++)
	{
		ObejectDetail detail;
		string delim(",");
		string Attr = m_config.get_value(m_sections[i], "AttributeList");
		string Property = m_config.get_value(m_sections[i], "PorpertyList");
		detail.attributes = split(Attr,delim);
		detail.properties = split(Property,delim);
		
		m_Content.insert(pair<string, ObejectDetail>(m_sections[i],detail));
	}
}


vector<string> ObjectCfg::getAttributeByName(const string &Name)
{
	vector<string > ret;
	map<string, ObejectDetail>::iterator it = m_Content.find(Name);
	if (it != m_Content.end())
	{
		ret = m_Content[Name].attributes;
	}

	return ret;
}
vector<string> ObjectCfg::getPropertyByName(const string &Name)
{
	vector<string > ret;
	map<string, ObejectDetail>::iterator it = m_Content.find(Name);
	if (it != m_Content.end())
	{
		ret = m_Content[Name].properties;
	}
	return ret;
}

ObejectDetail*  ObjectCfg::getDetailByName(const string &Name)
{

	map<string, ObejectDetail>::iterator it = m_Content.find(Name);
	if (it != m_Content.end())
	{
		return  &m_Content[Name];
	}
	return NULL;
}