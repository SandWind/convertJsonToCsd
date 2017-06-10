#include "XcsdFile.h"
#include<iostream>
#include"DictionaryHelper.h"

XcsdFile::XcsdFile()
{
	m_pDoc = new tinyxml2::XMLDocument();
	m_Root = NULL;
}

XcsdFile::XcsdFile(string FilePath)
{
	if (FilePath.length() > 0)
	{
		FILE* fp = NULL;
		fp = fopen(FilePath.c_str(), "w+");
		fclose(fp);
		m_pDoc = new tinyxml2::XMLDocument();
		m_pDoc->LoadFile(FilePath.c_str());
		m_Root = NULL;
		m_filePath = FilePath;
	}
}

XcsdFile::XcsdFile(string FilePath, string CfgFilePath)
{
	if (FilePath.length() > 0)
	{
		FILE* fp = NULL;
		fp = fopen(FilePath.c_str(), "w+");
		fclose(fp);
		m_pDoc = new tinyxml2::XMLDocument();
		m_pDoc->LoadFile(FilePath.c_str());
		m_Root = NULL;
		m_filePath = FilePath;
	}
	if (CfgFilePath.length() > 0)
	{
		m_pConfig = new ObjectCfg(CfgFilePath);
	}
}

XcsdFile::~XcsdFile()
{
	
	m_pDoc->Clear();
	m_Root = NULL;
	DICTOOL->destroyInstance();
	delete m_pDoc;
	delete m_pConfig;

}

void  XcsdFile::BeginCsd()
{
	m_Root = m_pDoc->NewElement("GameFile");
	m_pDoc->InsertEndChild(m_Root);
}

void  XcsdFile::EndCsd()
{	
	m_pDoc->SaveFile(m_filePath.c_str());
}

void XcsdFile::WritePropertyGroup(const Value &value)
{
	
	tinyxml2::XMLElement *group = m_pDoc->NewElement("PropertyGroup");
	group->SetAttribute("Name", DICTOOL->getValue_json(value, "Name"));
	group->SetAttribute("Type", DICTOOL->getValue_json(value, "Type"));
	group->SetAttribute("ID", DICTOOL->getStringValue_json(value, "ID"));
	group->SetAttribute("Name", DICTOOL->getValue_json(value, "Name"));
	group->SetAttribute("Version", DICTOOL->getValue_json(value, "Version"));
	m_Root->InsertEndChild(group);
}

void XcsdFile::WriteContent(const Value &value)
{
	const Value& content = DICTOOL->getSubDictionary_json(value, "Content");
	const Value& SecondContent = DICTOOL->getSubDictionary_json(content, "Content");
	
	tinyxml2::XMLElement *XmlContent = m_pDoc->NewElement("Content");
	XmlContent->SetAttribute("ctype", "GameProjectContent");
	/*if (0 == strcmp("GameFileData", DICTOOL->getStringValue_json(SecondContent, "ctype")))
	{
		
	}*/
	
	m_Root->InsertEndChild(XmlContent);

	tinyxml2::XMLElement *XmlinerContent = m_pDoc->NewElement("Content");
	XmlContent->InsertEndChild(XmlinerContent);
	WriteInerContent(XmlinerContent, SecondContent);
}

void XcsdFile::WriteInerContent(tinyxml2::XMLElement *parent,const Value &value)
{
	tinyxml2::XMLElement *XmlAnimation = m_pDoc->NewElement("Animation");
	const Value& Animation = DICTOOL->getSubDictionary_json(value, "Animation");
	XmlAnimation->SetAttribute("Duration", DICTOOL->getValue_json(Animation, "Duration"));
	XmlAnimation->SetAttribute("Speed", DICTOOL->getValue_json(Animation, "Speed"));
	parent->InsertEndChild(XmlAnimation);
	WriteObject(parent, value);

	
}

void XcsdFile::WriteObject(tinyxml2::XMLElement *parent, const Value& value)
{
	const Value& jsonObjectData = DICTOOL->getSubDictionary_json(value, "ObjectData");
	const Value& jsonSize       = DICTOOL->getSubDictionary_json(jsonObjectData, "Size");

	XMLElement *XmlObjectData = m_pDoc->NewElement("ObjectData");
	XmlObjectData->SetAttribute("Name", DICTOOL->getValue_json(jsonObjectData, "Name"));
	XmlObjectData->SetAttribute("Tag", DICTOOL->getValue_json(jsonObjectData, "Tag"));
	if (0 == strcmp("LayerObjectData", DICTOOL->getValue_json(jsonObjectData, "ctype")))
	{
		XmlObjectData->SetAttribute("ctype", "GameLayerObjectData");
	}
	
	parent->InsertEndChild(XmlObjectData);
	
	tinyxml2::XMLElement *XmlSize = m_pDoc->NewElement("Size");
	XmlSize->SetAttribute("X", DICTOOL->getValue_json(jsonSize, "X"));
	XmlSize->SetAttribute("Y", DICTOOL->getValue_json(jsonSize, "Y"));
	XmlObjectData->InsertEndChild(XmlSize);
	
	
	
	if (DICTOOL->checkObjectExist_json(jsonObjectData, "Children"))
	{
	   const Value& children = DICTOOL->getSubDictionary_json(jsonObjectData, "Children");
	   if (DICTOOL->getArrayCount_json(jsonObjectData,"Children") > 0)
	   {
		   WriteObjectForChildren(XmlObjectData, children);
	   }
	}

}

void XcsdFile::WriteObjectForChildren(tinyxml2::XMLElement *parent, const Value& children)
{
	tinyxml2::XMLElement *XmlChildren = m_pDoc->NewElement("Children");
	parent->InsertEndChild(XmlChildren);
	for (auto &m : children.GetArray())
	{ 
		const Value& child = m;
		tinyxml2::XMLElement *XmlNodeData = m_pDoc->NewElement("AbstractNodeData");
		XmlChildren->InsertEndChild(XmlNodeData);
		if (child.IsObject())
		{
			string ctype(DICTOOL->getValue_json(child, "ctype"));
			if (ctype.length() > 0)
			{
				ObejectDetail *detail = m_pConfig->getDetailByName(ctype);
				WriteObjectAttribute(XmlNodeData, child,detail);
			}
			
			//WriteSingleJsonObject(XmlNodeData, child);

			
		}
		else if(child.IsNull())
		{
			continue;
		}
		
	}
	
	
}



void XcsdFile::WriteSingleJsonObject(tinyxml2::XMLElement *parent, const Value& child)
{
	for (Value::ConstMemberIterator iter = child.MemberBegin(); iter != child.MemberEnd(); ++iter)
	{
		const Value& jsonNode =iter->value;
		
		if (jsonNode.IsNull())
		{
			continue;
		}
		else
		{
			const char* str = DICTOOL->getValue_json(child, iter->name.GetString());
			parent->SetAttribute(iter->name.GetString(), str);
		}
	}
}


void XcsdFile::WriteObjectAttribute(tinyxml2::XMLElement *XmlNodeData, const Value& child, ObejectDetail *detail)
{
	if (detail && detail->attributes.size() > 0)
	{
		for(int i=0;i< detail->attributes.size() ; i++)
		{ 
			const char* Name = detail->attributes[i].c_str();
			
			if (child.HasMember(Name))
			{
				XmlNodeData->SetAttribute(Name, DICTOOL->getValue_json(child, Name));
			}
			else
			{
				if (detail->attributes[i] == "LeftEage")
				{
					XmlNodeData->SetAttribute(Name, "15");
				}
				else if (detail->attributes[i] == "RightEage")
				{
					XmlNodeData->SetAttribute(Name, "15");
				}
				else if (detail->attributes[i] == "TopEage")
				{
					XmlNodeData->SetAttribute(Name, "11");
				}
				else if (detail->attributes[i] == "BottomEage")
				{
					XmlNodeData->SetAttribute(Name, "11");
				}
				else if (detail->attributes[i] == "ColorAngle")
				{
					XmlNodeData->SetAttribute(Name, "90.0000");
				}
			}

		}
	}
	
	WriteObjectProperty(XmlNodeData, child, detail);

	
}


void XcsdFile::WriteObjectProperty(tinyxml2::XMLElement *XmlNodeData, const Value& child, ObejectDetail *detail)
{

	if (detail && detail->properties.size() > 0)
	{
		for (int i = 0; i< detail->properties.size(); i++)
		{

			const char* Name = detail->properties[i].c_str();
			if (child.HasMember(Name))
			{
				tinyxml2::XMLElement *XmlProperty = m_pDoc->NewElement(Name);
				XmlNodeData->InsertEndChild(XmlProperty);
				const Value& josnProperty = DICTOOL->getSubDictionary_json(child, Name);
				WriteDefaultProperty(XmlProperty, josnProperty, detail->properties[i]);
				WriteSingleJsonObject(XmlProperty, josnProperty);
				if ("Size" == detail->properties[i])
				{
					if (DICTOOL->checkObjectExist_json(child, "Children"))
					{
						const Value& children = DICTOOL->getSubDictionary_json(child, "Children");
						if (DICTOOL->getArrayCount_json(child, "Children") > 0)
						{
							WriteObjectForChildren(XmlNodeData, children);
						}
					}
				}
			}
			
		}
	}
	
}



void XcsdFile::WriteDefaultProperty(tinyxml2::XMLElement *XmlNodeData, const Value& child, string Name)
{
	if (Name != "ColorVector")
	{
		if (Name.find("Color") != string::npos)
		{
			if (!child.HasMember("A"))
			{
				XmlNodeData->SetAttribute("A", "255");
			}
			if (!child.HasMember("R"))
			{
				XmlNodeData->SetAttribute("R", "255");
			}
			if (!child.HasMember("G"))
			{
				XmlNodeData->SetAttribute("G", "255");
			}
			if (!child.HasMember("B"))
			{
				XmlNodeData->SetAttribute("B", "255");
			}
		}
	}
	
}