// TestLanguageDesing.cpp : Defines the entry point for the application.
//

#include "TestLanguageDesing.h"

using namespace std;



ObjectHandler mainHandler;

ObjectMetadata::ObjectMetadata()
{
}

bool ObjectMetadata::isArray() const {
	return this->ArrayLength > 0;
}

bool ObjectMetadata::isFree() const {
	return this->Id < 0;
}



int16_t  Reference::getId()  const {
	return this->Id & INT_FAST16_MAX;
}
bool Reference::isOwner() const {
	return 	this->Id < 0;
}

bool Reference::isValid() const {
	ObjectMetadata metadata;
	return mainHandler.GetMetadata(*this, metadata) == GetMetadataStatus::Success;
}



ObjectHandler::ObjectHandler() {

}

GetMetadataStatus ObjectHandler::GetMetadata(const MetadataPointer& pointer, ObjectMetadata& metadata) {
	if (data.size() >= pointer)
		return GetMetadataStatus::Deleted;
	metadata = data.at(pointer);
	return GetMetadataStatus::Success;
}
GetMetadataStatus ObjectHandler::GetMetadata(_In_ const Reference& pointer, _Out_  ObjectMetadata& metadata) {
	ObjectMetadata result;
	if (GetMetadata(pointer.metadata, result) != GetMetadataStatus::Success)
		return GetMetadataStatus::Deleted;
	if (result.Id == pointer.getId()) {
		metadata = result;
		return GetMetadataStatus::Success;
	}
	return GetMetadataStatus::Deleted;
}

DeleteStatus ObjectHandler::Delete(_In_ const Reference& pointer) {
	if (!pointer.isOwner())
		return  DeleteStatus::NotOwner;

	ObjectMetadata metadata;
	if (GetMetadata(pointer, metadata) != GetMetadataStatus::Success) {
		return DeleteStatus::NotValid;
	}

	metadata.Id = -metadata.Id;
	return DeleteStatus::Success;
}

bool ObjectHandler::LoadType(_In_ TypeData& t, _Out_ ObjectMetadata& metadata) {
	
	metadata = {};
	metadata.Type = 

	return true;
}

bool ObjectHandler::AllocateInstance(_In_ ObjectMetadata& t, _Out_ ObjectMetadata& metadata) {
	metadata = {};
	return true;
}






int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}
