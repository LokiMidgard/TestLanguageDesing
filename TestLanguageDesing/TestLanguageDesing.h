// TestLanguageDesing.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

using  MetadataPointer = uint16_t;



struct ObjectMetadata {
	uint16_t OwnerThread; // 0 is shared
	int16_t Id; // negative is deleted
	uint16_t ArrayLength; // zero is no array
	MetadataPointer Type;
	void* object;
	uint16_t ObjectSize; // 

public:

	ObjectMetadata();

	bool isArray() const;

	bool isFree() const;
};

struct Reference
{
private:
	int16_t Id;

public:
	MetadataPointer metadata;

	int16_t  getId()  const;
	bool isOwner() const;

	bool isValid() const;

};

enum class GetMetadataStatus
{
	Success,
	Deleted,
};

enum class DeleteStatus
{
	Success,
	NotOwner,
	NotValid,
};



enum class Instructions : uint_fast8_t
{

};


struct FieldData
{

};


struct MethodData
{
	std::vector<Instructions> instructions;
};


struct TypeData {

public:
	wstring name;
	std::vector< FieldData> fields;
	std::vector< MethodData> methods;
};




struct ObjectHandler {

private:
	std::vector<ObjectMetadata> data;

public:

	ObjectHandler();

	_Check_return_
		_Success_(return == GetMetadataStatus::Success)
		GetMetadataStatus GetMetadata(_In_ const MetadataPointer& pointer, _Out_  ObjectMetadata& metadata);
	_Check_return_
		_Success_(return == GetMetadataStatus::Success)
		GetMetadataStatus GetMetadata(_In_ const Reference& pointer, _Out_  ObjectMetadata& metadata);

	DeleteStatus Delete(_In_ const Reference& pointer);

	bool LoadType(_In_ TypeData& t, _Out_ ObjectMetadata& metadata);

	bool AllocateInstance(_In_ ObjectMetadata& t, _Out_ ObjectMetadata& metadata);

};


// TODO: Reference additional headers your program requires here.
