#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT, // PREFAB // 완성품 // 블루프린트
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};

class Object
{
public:
	Object(OBJECT_TYPE type);
	virtual ~Object(); // 최상위기때문에 버츄얼

	OBJECT_TYPE GetType() { return _objectType; }

	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }

	// TODO : Instantiate(오브젝트를 복사할 수 있음)

protected:

	//리소스는 파일에 저장하고 불러 올 수 있어야하기 때문
	friend class Resources; // 리소스 매니저
	virtual void Load(const wstring& path) { }
	virtual void Save(const wstring& path) { }

protected:
	OBJECT_TYPE _objectType = OBJECT_TYPE::NONE;
	wstring _name;
};

