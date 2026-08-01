#ifndef __KERNEL_DEFS_H_
#define __KERNEL_DEFS_H_

#include "types.h"
//#include "dynamic_libs/fs_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FS_MAX_ENTNAME_SIZE 256

// original structure in the kernel that is originally 0x1270 long
typedef struct
{
    u32 version_cos_xml;           // version tag from cos.xml
    u64 os_version;                // os_version from app.xml
    u64 title_id;                  // title_id tag from app.xml
    u32 app_type;                  // app_type tag from app.xml
    u32 cmdFlags;                  // unknown tag as it is always 0 (might be cmdFlags from cos.xml but i am not sure)
    char rpx_name[0x1000];              // rpx name from cos.xml
    u32 unknown2;                  // 0x050B8304 in mii maker and system menu (looks a bit like permissions complex that got masked!?)
    u32 unknown3[63];              // those were all zeros, but its probably connected with unknown2
    u32 max_size;                  // max_size in cos.xml which defines the maximum amount of memory reserved for the app
    u32 avail_size;                // avail_size or codegen_size in cos.xml (seems to mostly be 0?)
    u32 codegen_size;              // codegen_size or avail_size in cos.xml (seems to mostly be 0?)
    u32 codegen_core;              // codegen_core in cos.xml (seems to mostly be 1?)
    u32 max_codesize;              // max_codesize in cos.xml
    u32 overlay_arena;             // overlay_arena in cos.xml
    u32 unknown4[59];              // all zeros it seems
    u32 default_stack0_size;       // not sure because always 0 but very likely
    u32 default_stack1_size;       // not sure because always 0 but very likely
    u32 default_stack2_size;       // not sure because always 0 but very likely
    u32 default_redzone0_size;     // not sure because always 0 but very likely
    u32 default_redzone1_size;     // not sure because always 0 but very likely
    u32 default_redzone2_size;     // not sure because always 0 but very likely
    u32 exception_stack0_size;     // from cos.xml, 0x1000 on mii maker
    u32 exception_stack1_size;     // from cos.xml, 0x1000 on mii maker
    u32 exception_stack2_size;     // from cos.xml, 0x1000 on mii maker
    u32 sdk_version;               // from app.xml, 20909 (0x51AD) on mii maker
    u32 title_version;             // from app.xml, 0x32 on mii maker
    /*
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    // the next part might be changing from title to title?! I don't think its important but nice to know maybe....
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    char mlc[4];                        // string "mlc" on mii maker and sysmenu
    u32 unknown5[7];               // all zeros on mii maker and sysmenu
    u32 unknown6_one;              // 0x01 on mii maker and sysmenu
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    char ACP[4];                        // string "ACP" on mii maker and sysmenu
    u32 unknown7[15];              // all zeros on mii maker and sysmenu
    u32 unknown8_5;                // 0x05 on mii maker and sysmenu
    u32 unknown9_zero;             // 0x00 on mii maker and sysmenu
    u32 unknown10_ptr;             // 0xFF23DD0C pointer on mii maker and sysmenu
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    char UVD[4];                        // string "UVD" on mii maker and sysmenu
    u32 unknown11[15];             // all zeros on mii maker and sysmenu
    u32 unknown12_5;               // 0x05 on mii maker and sysmenu
    u32 unknown13_zero;            // 0x00 on mii maker and sysmenu
    u32 unknown14_ptr;             // 0xFF23EFC8 pointer on mii maker and sysmenu
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    char SND[4];                        // string "SND" on mii maker and sysmenu
    u32 unknown15[15];             // all zeros on mii maker and sysmenu
    u32 unknown16_5;               // 0x05 on mii maker and sysmenu
    u32 unknown17_zero;            // 0x00 on mii maker and sysmenu
    u32 unknown18_ptr;             // 0xFF23F014 pointer on mii maker and sysmenu
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    u32 unknown19;                 // 0x02 on miimaker, 0x0F on system menu
    */
    // after that only zeros follow
} __attribute__((packed)) CosAppXmlInfo;


// Our own cos/app.xml struct which uses only uses as much memory as really needed, since many things are just zeros in the above structure
// This structure is only 0x64 bytes long + RPX name length (dynamic up to 0x1000 theoretically)
typedef struct
{
    u32 version_cos_xml;           // version tag from cos.xml
    u64 os_version;                // os_version from app.xml
    u64 title_id;                  // title_id tag from app.xml
    u32 app_type;                  // app_type tag from app.xml
    u32 cmdFlags;                  // unknown tag as it is always 0 (might be cmdFlags from cos.xml but i am not sure)
    u32 max_size;                  // max_size in cos.xml which defines the maximum amount of memory reserved for the app
    u32 avail_size;                // avail_size or codegen_size in cos.xml (seems to mostly be 0?)
    u32 codegen_size;              // codegen_size or avail_size in cos.xml (seems to mostly be 0?)
    u32 codegen_core;              // codegen_core in cos.xml (seems to mostly be 1?)
    u32 max_codesize;              // max_codesize in cos.xml
    u32 overlay_arena;             // overlay_arena in cos.xml
    u32 default_stack0_size;       // not sure because always 0 but very likely
    u32 default_stack1_size;       // not sure because always 0 but very likely
    u32 default_stack2_size;       // not sure because always 0 but very likely
    u32 default_redzone0_size;     // not sure because always 0 but very likely
    u32 default_redzone1_size;     // not sure because always 0 but very likely
    u32 default_redzone2_size;     // not sure because always 0 but very likely
    u32 exception_stack0_size;     // from cos.xml, 0x1000 on mii maker
    u32 exception_stack1_size;     // from cos.xml, 0x1000 on mii maker
    u32 exception_stack2_size;     // from cos.xml, 0x1000 on mii maker
    u32 sdk_version;               // from app.xml, 20909 (0x51AD) on mii maker
    u32 title_version;             // from app.xml, 0x32 on mii maker
    char rpx_name[FS_MAX_ENTNAME_SIZE]; // rpx name from cos.xml, length 256 as it can't get bigger from FS anyway
} __attribute__((packed)) ReducedCosAppXmlInfo;

typedef struct _bat_t
{
    u32 h;
    u32 l;
} bat_t;

typedef struct _bat_table_t
{
    bat_t bat[8];
} bat_table_t;

#ifdef __cplusplus
}
#endif

#endif // __KERNEL_DEFS_H_
