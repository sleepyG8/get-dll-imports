#include <Windows.h>
#include <winnt.h>
#include <stdio.h>
int main(int argc, char* argv[]) {

HMODULE hMod = LoadLibraryEx(argv[1], NULL, 0);
if (!hMod) {
    printf("error 1\n");
    return 1;
}

PIMAGE_DOS_HEADER dh = (PIMAGE_DOS_HEADER)hMod;
if (dh->e_magic != IMAGE_DOS_SIGNATURE) {
    printf("error 3 %lu\n", GetLastError());
    return 1;
} else {
    printf("Valdid PE file: %x\n", dh->e_magic);
}


PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((BYTE*)dh + dh->e_lfanew);
if (nt->Signature != IMAGE_NT_SIGNATURE) {
    printf("error 2\n");
    return 1;
}


PIMAGE_OPTIONAL_HEADER oh = &nt->OptionalHeader;

if (oh->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress == 0) {
    printf("Does not have any imports.\n");
    return 1;
}

PIMAGE_IMPORT_DESCRIPTOR id = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)oh->ImageBase + oh->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

while (id->Name != 0) {
    printf("Import: %s\n", (char*)oh->ImageBase + id->Name);
    printf("Characteristics: %x\n", id->Characteristics);
    id++; // Move to the next descriptor
}
return 0;
}

