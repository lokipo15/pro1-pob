/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.4.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // C:/Users/Konrad/Desktop/CLion/pro1-pob/resources/maps/level1.txt
  0x0,0x0,0x0,0x7b,
  0x0,
  0x0,0x3,0x9a,0x78,0xda,0xb5,0x93,0xe1,0xa,0xc0,0x20,0x8,0x84,0xff,0xf,0xf6,
  0xe,0x81,0xff,0xef,0xfd,0x1f,0x6f,0x53,0x97,0xd9,0x50,0x9,0xa2,0x63,0x48,0xf2,
  0xd5,0xed,0xc6,0x8c,0x28,0xd7,0x7d,0x11,0x9c,0x68,0xee,0x98,0xf2,0x2e,0x29,0x5c,
  0x6d,0xc1,0x65,0x97,0xa6,0xf2,0x67,0xd1,0x93,0x22,0x72,0x4e,0xa8,0xfb,0x16,0x5f,
  0xd5,0x79,0xc4,0xa0,0x26,0x8f,0xb5,0xeb,0xb4,0x99,0x42,0xda,0x53,0xad,0x53,0x35,
  0x83,0x18,0x7e,0xf4,0x6d,0xf7,0x3c,0xcf,0xa5,0x3d,0x39,0x33,0x7f,0x43,0x7b,0x85,
  0xa6,0x42,0xf4,0xdf,0xd1,0x33,0x57,0xb4,0x9e,0xa,0x8c,0x3b,0xe1,0x1d,0x7c,0xe6,
  0x9c,0x96,0x93,0x5c,0xe8,0x1,0xe1,0x3c,0x82,0x8f,
  
};

static const unsigned char qt_resource_name[] = {
  // maps
  0x0,0x4,
  0x0,0x7,0x38,0x73,
  0x0,0x6d,
  0x0,0x61,0x0,0x70,0x0,0x73,
    // level1.txt
  0x0,0xa,
  0xb,0xfe,0x2,0x74,
  0x0,0x6c,
  0x0,0x65,0x0,0x76,0x0,0x65,0x0,0x6c,0x0,0x31,0x0,0x2e,0x0,0x74,0x0,0x78,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/maps
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/maps/level1.txt
  0x0,0x0,0x0,0xe,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x96,0xfd,0x95,0x29,0x4c,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#if defined(__ELF__) || defined(__APPLE__)
static inline unsigned char qResourceFeatureZlib()
{
    extern const unsigned char qt_resourceFeatureZlib;
    return qt_resourceFeatureZlib;
}
#else
unsigned char qResourceFeatureZlib();
#endif

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)()
{
    int version = 3;
    version += QT_RCC_PREPEND_NAMESPACE(qResourceFeatureZlib());
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)(); }
   } dummy;
}
