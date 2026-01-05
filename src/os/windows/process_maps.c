#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "process_maps.h"

#define REGION_SIZE_DEFAULT     16

static uint32_t windows_protect_to_perms(DWORD protect) {
    uint32_t p = 0;

    if (protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ |
                   PAGE_EXECUTE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_WRITECOPY)) {
        p |= 0x1;
                   }

    if (protect & (PAGE_READWRITE | PAGE_EXECUTE_READWRITE |
                   PAGE_WRITECOPY | PAGE_EXECUTE_WRITECOPY)) {
        p |= 0x2;
                   }

    if (protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ |
                   PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) {
        p |= 0x4;
                   }

    return p;
}


mf_error_t mf_windows_enumerate_maps(
    struct mf_process *process,
    struct mf_mem_region **regions,
    size_t *count
)
{
    if (process == NULL || regions == NULL || count == NULL) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    MEMORY_BASIC_INFORMATION mem_info;
    SYSTEM_INFO system_info = {0};

    size_t region_count = 0;
    uint32_t region_capacity = REGION_SIZE_DEFAULT;

    struct mf_mem_region *region_list = calloc(REGION_SIZE_DEFAULT, sizeof(struct mf_mem_region));
    GetSystemInfo(&system_info);

    LPVOID address = system_info.lpMinimumApplicationAddress;

    while (VirtualQueryEx(process->os_handle, address, &mem_info, sizeof(mem_info))) {
        struct mf_mem_region current_region;

        if (mem_info.State == MEM_COMMIT) {
            current_region.start = (uintptr_t)mem_info.BaseAddress;
            current_region.end = (uintptr_t)mem_info.BaseAddress + mem_info.RegionSize;
            current_region.permissions = windows_protect_to_perms(mem_info.Protect);

            if (region_capacity == region_count) {
                region_capacity <<= 1;

                struct mf_mem_region *tmp = realloc(region_list, region_capacity * sizeof(struct mf_mem_region));

                if (tmp == NULL) {
                    free(region_list);
                    return MF_ERR_NO_MEMORY;
                }

                region_list = tmp;
            }

            memcpy(&region_list[region_count], &current_region, sizeof(current_region));
            region_count++;
        }
        address += mem_info.RegionSize;
    }

    *regions = region_list;
    *count = region_count;
    return MF_OK;
}
