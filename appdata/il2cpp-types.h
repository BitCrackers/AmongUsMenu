// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Target Unity version: 2021.1.0+

#if defined(_GHIDRA_) || defined(_IDA_)
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
#endif

#if defined(_GHIDRA_)
typedef __int32 size_t;
typedef size_t intptr_t;
typedef size_t uintptr_t;
#endif

#if !defined(_GHIDRA_) && !defined(_IDA_)
#define _CPLUSPLUS_
#endif

// ******************************************************************************
// * IL2CPP internal types
// ******************************************************************************
#pragma region il2cpp_internal
//{ il2cpp_internal_scintilla

#define IS_32BIT
typedef struct Il2CppClass Il2CppClass;
typedef struct Il2CppType Il2CppType;
typedef struct EventInfo EventInfo;
typedef struct MethodInfo MethodInfo;
typedef struct FieldInfo FieldInfo;
typedef struct PropertyInfo PropertyInfo;
typedef struct Il2CppAssembly Il2CppAssembly;
typedef struct Il2CppArray Il2CppArray;
typedef struct Il2CppDelegate Il2CppDelegate;
typedef struct Il2CppDomain Il2CppDomain;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppException Il2CppException;
typedef struct Il2CppProfiler Il2CppProfiler;
typedef struct Il2CppObject Il2CppObject;
typedef struct Il2CppReflectionMethod Il2CppReflectionMethod;
typedef struct Il2CppReflectionType Il2CppReflectionType;
typedef struct Il2CppString Il2CppString;
typedef struct Il2CppThread Il2CppThread;
typedef struct Il2CppAsyncResult Il2CppAsyncResult;
typedef struct Il2CppManagedMemorySnapshot Il2CppManagedMemorySnapshot;
typedef struct Il2CppCustomAttrInfo Il2CppCustomAttrInfo;
typedef enum
{
    IL2CPP_PROFILE_NONE = 0,
    IL2CPP_PROFILE_APPDOMAIN_EVENTS = 1 << 0,
    IL2CPP_PROFILE_ASSEMBLY_EVENTS = 1 << 1,
    IL2CPP_PROFILE_MODULE_EVENTS = 1 << 2,
    IL2CPP_PROFILE_CLASS_EVENTS = 1 << 3,
    IL2CPP_PROFILE_JIT_COMPILATION = 1 << 4,
    IL2CPP_PROFILE_INLINING = 1 << 5,
    IL2CPP_PROFILE_EXCEPTIONS = 1 << 6,
    IL2CPP_PROFILE_ALLOCATIONS = 1 << 7,
    IL2CPP_PROFILE_GC = 1 << 8,
    IL2CPP_PROFILE_THREADS = 1 << 9,
    IL2CPP_PROFILE_REMOTING = 1 << 10,
    IL2CPP_PROFILE_TRANSITIONS = 1 << 11,
    IL2CPP_PROFILE_ENTER_LEAVE = 1 << 12,
    IL2CPP_PROFILE_COVERAGE = 1 << 13,
    IL2CPP_PROFILE_INS_COVERAGE = 1 << 14,
    IL2CPP_PROFILE_STATISTICAL = 1 << 15,
    IL2CPP_PROFILE_METHOD_EVENTS = 1 << 16,
    IL2CPP_PROFILE_MONITOR_EVENTS = 1 << 17,
    IL2CPP_PROFILE_IOMAP_EVENTS = 1 << 18,
    IL2CPP_PROFILE_GC_MOVES = 1 << 19,
    IL2CPP_PROFILE_FILEIO = 1 << 20
} Il2CppProfileFlags;
typedef enum
{
    IL2CPP_PROFILE_FILEIO_WRITE = 0,
    IL2CPP_PROFILE_FILEIO_READ
} Il2CppProfileFileIOKind;
typedef enum
{
    IL2CPP_GC_EVENT_START,
    IL2CPP_GC_EVENT_MARK_START,
    IL2CPP_GC_EVENT_MARK_END,
    IL2CPP_GC_EVENT_RECLAIM_START,
    IL2CPP_GC_EVENT_RECLAIM_END,
    IL2CPP_GC_EVENT_END,
    IL2CPP_GC_EVENT_PRE_STOP_WORLD,
    IL2CPP_GC_EVENT_POST_STOP_WORLD,
    IL2CPP_GC_EVENT_PRE_START_WORLD,
    IL2CPP_GC_EVENT_POST_START_WORLD
} Il2CppGCEvent;
typedef enum
{
    IL2CPP_GC_MODE_DISABLED = 0,
    IL2CPP_GC_MODE_ENABLED = 1,
    IL2CPP_GC_MODE_MANUAL = 2
} Il2CppGCMode;
typedef enum
{
    IL2CPP_STAT_NEW_OBJECT_COUNT,
    IL2CPP_STAT_INITIALIZED_CLASS_COUNT,
    IL2CPP_STAT_METHOD_COUNT,
    IL2CPP_STAT_CLASS_STATIC_DATA_SIZE,
    IL2CPP_STAT_GENERIC_INSTANCE_COUNT,
    IL2CPP_STAT_GENERIC_CLASS_COUNT,
    IL2CPP_STAT_INFLATED_METHOD_COUNT,
    IL2CPP_STAT_INFLATED_TYPE_COUNT,
} Il2CppStat;
typedef enum
{
    IL2CPP_UNHANDLED_POLICY_LEGACY,
    IL2CPP_UNHANDLED_POLICY_CURRENT
} Il2CppRuntimeUnhandledExceptionPolicy;
typedef struct Il2CppStackFrameInfo
{
    const MethodInfo* method;
    uintptr_t raw_ip;
    int sourceCodeLineNumber;
    int ilOffset;
    const char* filePath;
} Il2CppStackFrameInfo;
typedef void(*Il2CppMethodPointer)();
typedef struct Il2CppMethodDebugInfo
{
    Il2CppMethodPointer methodPointer;
    int32_t code_size;
    const char* file;
} Il2CppMethodDebugInfo;
typedef struct
{
    void* (*malloc_func)(size_t size);
    void* (*aligned_malloc_func)(size_t size, size_t alignment);
    void (*free_func)(void* ptr);
    void (*aligned_free_func)(void* ptr);
    void* (*calloc_func)(size_t nmemb, size_t size);
    void* (*realloc_func)(void* ptr, size_t size);
    void* (*aligned_realloc_func)(void* ptr, size_t size, size_t alignment);
} Il2CppMemoryCallbacks;
typedef struct
{
    const char* name;
    void(*connect)(const char* address);
    int(*wait_for_attach)(void);
    void(*close1)(void);
    void(*close2)(void);
    int(*send)(void* buf, int len);
    int(*recv)(void* buf, int len);
} Il2CppDebuggerTransport;
typedef uint16_t Il2CppChar;
typedef char Il2CppNativeChar;
typedef void (*il2cpp_register_object_callback)(Il2CppObject** arr, int size, void* userdata);
typedef void (*il2cpp_WorldChangedCallback)();
typedef void (*Il2CppFrameWalkFunc) (const Il2CppStackFrameInfo* info, void* user_data);
typedef void (*Il2CppProfileFunc) (Il2CppProfiler* prof);
typedef void (*Il2CppProfileMethodFunc) (Il2CppProfiler* prof, const MethodInfo* method);
typedef void (*Il2CppProfileAllocFunc) (Il2CppProfiler* prof, Il2CppObject* obj, Il2CppClass* klass);
typedef void (*Il2CppProfileGCFunc) (Il2CppProfiler* prof, Il2CppGCEvent event, int generation);
typedef void (*Il2CppProfileGCResizeFunc) (Il2CppProfiler* prof, int64_t new_size);
typedef void (*Il2CppProfileFileIOFunc) (Il2CppProfiler* prof, Il2CppProfileFileIOKind kind, int count);
typedef void (*Il2CppProfileThreadFunc) (Il2CppProfiler* prof, unsigned long tid);
typedef const Il2CppNativeChar* (*Il2CppSetFindPlugInCallback)(const Il2CppNativeChar*);
typedef void (*Il2CppLogCallback)(const char*);
typedef size_t(*Il2CppBacktraceFunc) (Il2CppMethodPointer* buffer, size_t maxSize);
typedef struct Il2CppManagedMemorySnapshot Il2CppManagedMemorySnapshot;
typedef uintptr_t il2cpp_array_size_t;
typedef void (*SynchronizationContextCallback)(intptr_t arg);
typedef uint16_t Il2CppMethodSlot;
static const uint16_t kInvalidIl2CppMethodSlot = 65535;
static const int ipv6AddressSize = 16;
typedef int32_t il2cpp_hresult_t;
typedef enum
{
    IL2CPP_TOKEN_MODULE = 0x00000000,
    IL2CPP_TOKEN_TYPE_REF = 0x01000000,
    IL2CPP_TOKEN_TYPE_DEF = 0x02000000,
    IL2CPP_TOKEN_FIELD_DEF = 0x04000000,
    IL2CPP_TOKEN_METHOD_DEF = 0x06000000,
    IL2CPP_TOKEN_PARAM_DEF = 0x08000000,
    IL2CPP_TOKEN_INTERFACE_IMPL = 0x09000000,
    IL2CPP_TOKEN_MEMBER_REF = 0x0a000000,
    IL2CPP_TOKEN_CUSTOM_ATTRIBUTE = 0x0c000000,
    IL2CPP_TOKEN_PERMISSION = 0x0e000000,
    IL2CPP_TOKEN_SIGNATURE = 0x11000000,
    IL2CPP_TOKEN_EVENT = 0x14000000,
    IL2CPP_TOKEN_PROPERTY = 0x17000000,
    IL2CPP_TOKEN_MODULE_REF = 0x1a000000,
    IL2CPP_TOKEN_TYPE_SPEC = 0x1b000000,
    IL2CPP_TOKEN_ASSEMBLY = 0x20000000,
    IL2CPP_TOKEN_ASSEMBLY_REF = 0x23000000,
    IL2CPP_TOKEN_FILE = 0x26000000,
    IL2CPP_TOKEN_EXPORTED_TYPE = 0x27000000,
    IL2CPP_TOKEN_MANIFEST_RESOURCE = 0x28000000,
    IL2CPP_TOKEN_GENERIC_PARAM = 0x2a000000,
    IL2CPP_TOKEN_METHOD_SPEC = 0x2b000000,
} Il2CppTokenType;
typedef int32_t TypeIndex;
typedef int32_t TypeDefinitionIndex;
typedef int32_t FieldIndex;
typedef int32_t DefaultValueIndex;
typedef int32_t DefaultValueDataIndex;
typedef int32_t CustomAttributeIndex;
typedef int32_t ParameterIndex;
typedef int32_t MethodIndex;
typedef int32_t GenericMethodIndex;
typedef int32_t PropertyIndex;
typedef int32_t EventIndex;
typedef int32_t GenericContainerIndex;
typedef int32_t GenericParameterIndex;
typedef int16_t GenericParameterConstraintIndex;
typedef int32_t NestedTypeIndex;
typedef int32_t InterfacesIndex;
typedef int32_t VTableIndex;
typedef int32_t RGCTXIndex;
typedef int32_t StringIndex;
typedef int32_t StringLiteralIndex;
typedef int32_t GenericInstIndex;
typedef int32_t ImageIndex;
typedef int32_t AssemblyIndex;
typedef int32_t InteropDataIndex;
typedef int32_t TypeFieldIndex;
typedef int32_t TypeMethodIndex;
typedef int32_t MethodParameterIndex;
typedef int32_t TypePropertyIndex;
typedef int32_t TypeEventIndex;
typedef int32_t TypeInterfaceIndex;
typedef int32_t TypeNestedTypeIndex;
typedef int32_t TypeInterfaceOffsetIndex;
typedef int32_t GenericContainerParameterIndex;
typedef int32_t AssemblyTypeIndex;
typedef int32_t AssemblyExportedTypeIndex;
static const TypeIndex kTypeIndexInvalid = -1;
static const TypeDefinitionIndex kTypeDefinitionIndexInvalid = -1;
static const DefaultValueDataIndex kDefaultValueIndexNull = -1;
static const CustomAttributeIndex kCustomAttributeIndexInvalid = -1;
static const EventIndex kEventIndexInvalid = -1;
static const FieldIndex kFieldIndexInvalid = -1;
static const MethodIndex kMethodIndexInvalid = -1;
static const PropertyIndex kPropertyIndexInvalid = -1;
static const GenericContainerIndex kGenericContainerIndexInvalid = -1;
static const GenericParameterIndex kGenericParameterIndexInvalid = -1;
static const RGCTXIndex kRGCTXIndexInvalid = -1;
static const StringLiteralIndex kStringLiteralIndexInvalid = -1;
static const InteropDataIndex kInteropDataIndexInvalid = -1;
static const int kPublicKeyByteLength = 8;
typedef struct Il2CppMethodSpec
{
    MethodIndex methodDefinitionIndex;
    GenericInstIndex classIndexIndex;
    GenericInstIndex methodIndexIndex;
} Il2CppMethodSpec;
typedef enum Il2CppRGCTXDataType
{
    IL2CPP_RGCTX_DATA_INVALID,
    IL2CPP_RGCTX_DATA_TYPE,
    IL2CPP_RGCTX_DATA_CLASS,
    IL2CPP_RGCTX_DATA_METHOD,
    IL2CPP_RGCTX_DATA_ARRAY,
} Il2CppRGCTXDataType;
typedef union Il2CppRGCTXDefinitionData
{
    int32_t rgctxDataDummy;
    MethodIndex __methodIndex;
    TypeIndex __typeIndex;
} Il2CppRGCTXDefinitionData;
typedef struct Il2CppRGCTXDefinition
{
    Il2CppRGCTXDataType type;
    const Il2CppRGCTXDefinitionData* data;
} Il2CppRGCTXDefinition;
typedef struct
{
    MethodIndex methodIndex;
    MethodIndex invokerIndex;
} Il2CppGenericMethodIndices;
typedef struct Il2CppGenericMethodFunctionsDefinitions
{
    GenericMethodIndex genericMethodIndex;
    Il2CppGenericMethodIndices indices;
} Il2CppGenericMethodFunctionsDefinitions;
static inline uint32_t GetTokenType(uint32_t token)
{
    return token & 0xFF000000;
}
static inline uint32_t GetTokenRowId(uint32_t token)
{
    return token & 0x00FFFFFF;
}
typedef const struct ___Il2CppMetadataImageHandle* Il2CppMetadataImageHandle;
typedef const struct ___Il2CppMetadataCustomAttributeHandle* Il2CppMetadataCustomAttributeHandle;
typedef const struct ___Il2CppMetadataTypeHandle* Il2CppMetadataTypeHandle;
typedef const struct ___Il2CppMetadataMethodHandle* Il2CppMetadataMethodDefinitionHandle;
typedef const struct ___Il2CppMetadataGenericContainerHandle* Il2CppMetadataGenericContainerHandle;
typedef const struct ___Il2CppMetadataGenericParameterHandle* Il2CppMetadataGenericParameterHandle;
typedef uint32_t EncodedMethodIndex;
typedef enum Il2CppMetadataUsage
{
    kIl2CppMetadataUsageInvalid,
    kIl2CppMetadataUsageTypeInfo,
    kIl2CppMetadataUsageIl2CppType,
    kIl2CppMetadataUsageMethodDef,
    kIl2CppMetadataUsageFieldInfo,
    kIl2CppMetadataUsageStringLiteral,
    kIl2CppMetadataUsageMethodRef,
} Il2CppMetadataUsage;
typedef struct Il2CppInterfaceOffsetPair
{
    TypeIndex interfaceTypeIndex;
    int32_t offset;
} Il2CppInterfaceOffsetPair;
typedef struct Il2CppTypeDefinition
{
    StringIndex nameIndex;
    StringIndex namespaceIndex;
    TypeIndex byvalTypeIndex;
    TypeIndex declaringTypeIndex;
    TypeIndex parentIndex;
    TypeIndex elementTypeIndex;
    GenericContainerIndex genericContainerIndex;
    uint32_t flags;
    FieldIndex fieldStart;
    MethodIndex methodStart;
    EventIndex eventStart;
    PropertyIndex propertyStart;
    NestedTypeIndex nestedTypesStart;
    InterfacesIndex interfacesStart;
    VTableIndex vtableStart;
    InterfacesIndex interfaceOffsetsStart;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint32_t bitfield;
    uint32_t token;
} Il2CppTypeDefinition;
typedef struct Il2CppFieldDefinition
{
    StringIndex nameIndex;
    TypeIndex typeIndex;
    uint32_t token;
} Il2CppFieldDefinition;
typedef struct Il2CppFieldDefaultValue
{
    FieldIndex fieldIndex;
    TypeIndex typeIndex;
    DefaultValueDataIndex dataIndex;
} Il2CppFieldDefaultValue;
typedef struct Il2CppFieldMarshaledSize
{
    FieldIndex fieldIndex;
    TypeIndex typeIndex;
    int32_t size;
} Il2CppFieldMarshaledSize;
typedef struct Il2CppFieldRef
{
    TypeIndex typeIndex;
    FieldIndex fieldIndex;
} Il2CppFieldRef;
typedef struct Il2CppParameterDefinition
{
    StringIndex nameIndex;
    uint32_t token;
    TypeIndex typeIndex;
} Il2CppParameterDefinition;
typedef struct Il2CppParameterDefaultValue
{
    ParameterIndex parameterIndex;
    TypeIndex typeIndex;
    DefaultValueDataIndex dataIndex;
} Il2CppParameterDefaultValue;
typedef struct Il2CppMethodDefinition
{
    StringIndex nameIndex;
    TypeDefinitionIndex declaringType;
    TypeIndex returnType;
    ParameterIndex parameterStart;
    GenericContainerIndex genericContainerIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint16_t parameterCount;
} Il2CppMethodDefinition;
typedef struct Il2CppEventDefinition
{
    StringIndex nameIndex;
    TypeIndex typeIndex;
    MethodIndex add;
    MethodIndex remove;
    MethodIndex raise;
    uint32_t token;
} Il2CppEventDefinition;
typedef struct Il2CppPropertyDefinition
{
    StringIndex nameIndex;
    MethodIndex get;
    MethodIndex set;
    uint32_t attrs;
    uint32_t token;
} Il2CppPropertyDefinition;
typedef struct Il2CppStringLiteral
{
    uint32_t length;
    StringLiteralIndex dataIndex;
} Il2CppStringLiteral;
typedef struct Il2CppAssemblyNameDefinition
{
    StringIndex nameIndex;
    StringIndex cultureIndex;
    StringIndex publicKeyIndex;
    uint32_t hash_alg;
    int32_t hash_len;
    uint32_t flags;
    int32_t major;
    int32_t minor;
    int32_t build;
    int32_t revision;
    uint8_t public_key_token[8];
} Il2CppAssemblyNameDefinition;
typedef struct Il2CppImageDefinition
{
    StringIndex nameIndex;
    AssemblyIndex assemblyIndex;
    TypeDefinitionIndex typeStart;
    uint32_t typeCount;
    TypeDefinitionIndex exportedTypeStart;
    uint32_t exportedTypeCount;
    MethodIndex entryPointIndex;
    uint32_t token;
    CustomAttributeIndex customAttributeStart;
    uint32_t customAttributeCount;
} Il2CppImageDefinition;
typedef struct Il2CppAssemblyDefinition
{
    ImageIndex imageIndex;
    uint32_t token;
    int32_t referencedAssemblyStart;
    int32_t referencedAssemblyCount;
    Il2CppAssemblyNameDefinition aname;
} Il2CppAssemblyDefinition;
typedef struct Il2CppCustomAttributeTypeRange
{
    uint32_t token;
    int32_t start;
    int32_t count;
} Il2CppCustomAttributeTypeRange;
typedef struct Il2CppMetadataRange
{
    int32_t start;
    int32_t length;
} Il2CppMetadataRange;
typedef struct Il2CppGenericContainer
{
    int32_t ownerIndex;
    int32_t type_argc;
    int32_t is_method;
    GenericParameterIndex genericParameterStart;
} Il2CppGenericContainer;
typedef struct Il2CppGenericParameter
{
    GenericContainerIndex ownerIndex;
    StringIndex nameIndex;
    GenericParameterConstraintIndex constraintsStart;
    int16_t constraintsCount;
    uint16_t num;
    uint16_t flags;
} Il2CppGenericParameter;
typedef struct Il2CppWindowsRuntimeTypeNamePair
{
    StringIndex nameIndex;
    TypeIndex typeIndex;
} Il2CppWindowsRuntimeTypeNamePair;
#pragma pack(push, p1,4)
typedef struct Il2CppGlobalMetadataHeader
{
    int32_t sanity;
    int32_t version;
    int32_t stringLiteralOffset;
    int32_t stringLiteralCount;
    int32_t stringLiteralDataOffset;
    int32_t stringLiteralDataCount;
    int32_t stringOffset;
    int32_t stringCount;
    int32_t eventsOffset;
    int32_t eventsCount;
    int32_t propertiesOffset;
    int32_t propertiesCount;
    int32_t methodsOffset;
    int32_t methodsCount;
    int32_t parameterDefaultValuesOffset;
    int32_t parameterDefaultValuesCount;
    int32_t fieldDefaultValuesOffset;
    int32_t fieldDefaultValuesCount;
    int32_t fieldAndParameterDefaultValueDataOffset;
    int32_t fieldAndParameterDefaultValueDataCount;
    int32_t fieldMarshaledSizesOffset;
    int32_t fieldMarshaledSizesCount;
    int32_t parametersOffset;
    int32_t parametersCount;
    int32_t fieldsOffset;
    int32_t fieldsCount;
    int32_t genericParametersOffset;
    int32_t genericParametersCount;
    int32_t genericParameterConstraintsOffset;
    int32_t genericParameterConstraintsCount;
    int32_t genericContainersOffset;
    int32_t genericContainersCount;
    int32_t nestedTypesOffset;
    int32_t nestedTypesCount;
    int32_t interfacesOffset;
    int32_t interfacesCount;
    int32_t vtableMethodsOffset;
    int32_t vtableMethodsCount;
    int32_t interfaceOffsetsOffset;
    int32_t interfaceOffsetsCount;
    int32_t typeDefinitionsOffset;
    int32_t typeDefinitionsCount;
    int32_t imagesOffset;
    int32_t imagesCount;
    int32_t assembliesOffset;
    int32_t assembliesCount;
    int32_t fieldRefsOffset;
    int32_t fieldRefsCount;
    int32_t referencedAssembliesOffset;
    int32_t referencedAssembliesCount;
    int32_t attributesInfoOffset;
    int32_t attributesInfoCount;
    int32_t attributeTypesOffset;
    int32_t attributeTypesCount;
    int32_t unresolvedVirtualCallParameterTypesOffset;
    int32_t unresolvedVirtualCallParameterTypesCount;
    int32_t unresolvedVirtualCallParameterRangesOffset;
    int32_t unresolvedVirtualCallParameterRangesCount;
    int32_t windowsRuntimeTypeNamesOffset;
    int32_t windowsRuntimeTypeNamesSize;
    int32_t windowsRuntimeStringsOffset;
    int32_t windowsRuntimeStringsSize;
    int32_t exportedTypeDefinitionsOffset;
    int32_t exportedTypeDefinitionsCount;
} Il2CppGlobalMetadataHeader;
#pragma pack(pop, p1)
typedef struct Il2CppMetadataField
{
    uint32_t offset;
    uint32_t typeIndex;
    const char* name;
    uint8_t isStatic;
} Il2CppMetadataField;
typedef enum Il2CppMetadataTypeFlags
{
    kNone = 0,
    kValueType = 1 << 0,
    kArray = 1 << 1,
    kArrayRankMask = 0xFFFF0000
} Il2CppMetadataTypeFlags;
typedef struct Il2CppMetadataType
{
    Il2CppMetadataTypeFlags flags;
    Il2CppMetadataField* fields;
    uint32_t fieldCount;
    uint32_t staticsSize;
    uint8_t* statics;
    uint32_t baseOrElementTypeIndex;
    char* name;
    const char* assemblyName;
    uint64_t typeInfoAddress;
    uint32_t size;
} Il2CppMetadataType;
typedef struct Il2CppMetadataSnapshot
{
    uint32_t typeCount;
    Il2CppMetadataType* types;
} Il2CppMetadataSnapshot;
typedef struct Il2CppManagedMemorySection
{
    uint64_t sectionStartAddress;
    uint32_t sectionSize;
    uint8_t* sectionBytes;
} Il2CppManagedMemorySection;
typedef struct Il2CppManagedHeap
{
    uint32_t sectionCount;
    Il2CppManagedMemorySection* sections;
} Il2CppManagedHeap;
typedef struct Il2CppStacks
{
    uint32_t stackCount;
    Il2CppManagedMemorySection* stacks;
} Il2CppStacks;
typedef struct NativeObject
{
    uint32_t gcHandleIndex;
    uint32_t size;
    uint32_t instanceId;
    uint32_t classId;
    uint32_t referencedNativeObjectIndicesCount;
    uint32_t* referencedNativeObjectIndices;
} NativeObject;
typedef struct Il2CppGCHandles
{
    uint32_t trackedObjectCount;
    uint64_t* pointersToObjects;
} Il2CppGCHandles;
typedef struct Il2CppRuntimeInformation
{
    uint32_t pointerSize;
    uint32_t objectHeaderSize;
    uint32_t arrayHeaderSize;
    uint32_t arrayBoundsOffsetInHeader;
    uint32_t arraySizeOffsetInHeader;
    uint32_t allocationGranularity;
} Il2CppRuntimeInformation;
typedef struct Il2CppManagedMemorySnapshot
{
    Il2CppManagedHeap heap;
    Il2CppStacks stacks;
    Il2CppMetadataSnapshot metadata;
    Il2CppGCHandles gcHandles;
    Il2CppRuntimeInformation runtimeInformation;
    void* additionalUserInformation;
} Il2CppManagedMemorySnapshot;
typedef enum Il2CppTypeEnum
{
    IL2CPP_TYPE_END = 0x00,
    IL2CPP_TYPE_VOID = 0x01,
    IL2CPP_TYPE_BOOLEAN = 0x02,
    IL2CPP_TYPE_CHAR = 0x03,
    IL2CPP_TYPE_I1 = 0x04,
    IL2CPP_TYPE_U1 = 0x05,
    IL2CPP_TYPE_I2 = 0x06,
    IL2CPP_TYPE_U2 = 0x07,
    IL2CPP_TYPE_I4 = 0x08,
    IL2CPP_TYPE_U4 = 0x09,
    IL2CPP_TYPE_I8 = 0x0a,
    IL2CPP_TYPE_U8 = 0x0b,
    IL2CPP_TYPE_R4 = 0x0c,
    IL2CPP_TYPE_R8 = 0x0d,
    IL2CPP_TYPE_STRING = 0x0e,
    IL2CPP_TYPE_PTR = 0x0f,
    IL2CPP_TYPE_BYREF = 0x10,
    IL2CPP_TYPE_VALUETYPE = 0x11,
    IL2CPP_TYPE_CLASS = 0x12,
    IL2CPP_TYPE_VAR = 0x13,
    IL2CPP_TYPE_ARRAY = 0x14,
    IL2CPP_TYPE_GENERICINST = 0x15,
    IL2CPP_TYPE_TYPEDBYREF = 0x16,
    IL2CPP_TYPE_I = 0x18,
    IL2CPP_TYPE_U = 0x19,
    IL2CPP_TYPE_FNPTR = 0x1b,
    IL2CPP_TYPE_OBJECT = 0x1c,
    IL2CPP_TYPE_SZARRAY = 0x1d,
    IL2CPP_TYPE_MVAR = 0x1e,
    IL2CPP_TYPE_CMOD_REQD = 0x1f,
    IL2CPP_TYPE_CMOD_OPT = 0x20,
    IL2CPP_TYPE_INTERNAL = 0x21,
    IL2CPP_TYPE_MODIFIER = 0x40,
    IL2CPP_TYPE_SENTINEL = 0x41,
    IL2CPP_TYPE_PINNED = 0x45,
    IL2CPP_TYPE_ENUM = 0x55
} Il2CppTypeEnum;
typedef struct Il2CppClass Il2CppClass;
typedef struct MethodInfo MethodInfo;
typedef struct Il2CppType Il2CppType;
typedef struct Il2CppArrayType
{
    const Il2CppType* etype;
    uint8_t rank;
    uint8_t numsizes;
    uint8_t numlobounds;
    int* sizes;
    int* lobounds;
} Il2CppArrayType;
typedef struct Il2CppGenericInst
{
    uint32_t type_argc;
    const Il2CppType** type_argv;
} Il2CppGenericInst;
typedef struct Il2CppGenericContext
{
    const Il2CppGenericInst* class_inst;
    const Il2CppGenericInst* method_inst;
} Il2CppGenericContext;
typedef struct Il2CppGenericClass
{
    const Il2CppType* type;
    Il2CppGenericContext context;
    Il2CppClass* cached_class;
} Il2CppGenericClass;
typedef struct Il2CppGenericMethod
{
    const MethodInfo* methodDefinition;
    Il2CppGenericContext context;
} Il2CppGenericMethod;
typedef struct Il2CppType
{
    union
    {
        void* dummy;
        TypeDefinitionIndex __klassIndex;
        Il2CppMetadataTypeHandle typeHandle;
        const Il2CppType* type;
        Il2CppArrayType* array;
        GenericParameterIndex __genericParameterIndex;
        Il2CppMetadataGenericParameterHandle genericParameterHandle;
        Il2CppGenericClass* generic_class;
    } data;
    unsigned int attrs : 16;
    Il2CppTypeEnum type : 8;
    unsigned int num_mods : 5;
    unsigned int byref : 1;
    unsigned int pinned : 1;
    unsigned int valuetype : 1;
} Il2CppType;
typedef struct Il2CppMetadataFieldInfo
{
    const Il2CppType* type;
    const char* name;
    uint32_t token;
} Il2CppMetadataFieldInfo;
typedef struct Il2CppMetadataMethodInfo
{
    Il2CppMetadataMethodDefinitionHandle handle;
    const char* name;
    const Il2CppType* return_type;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint16_t parameterCount;
} Il2CppMetadataMethodInfo;
typedef struct Il2CppMetadataParameterInfo
{
    const char* name;
    uint32_t token;
    const Il2CppType* type;
} Il2CppMetadataParameterInfo;
typedef struct Il2CppMetadataPropertyInfo
{
    const char* name;
    const MethodInfo* get;
    const MethodInfo* set;
    uint32_t attrs;
    uint32_t token;
} Il2CppMetadataPropertyInfo;
typedef struct Il2CppMetadataEventInfo
{
    const char* name;
    const Il2CppType* type;
    const MethodInfo* add;
    const MethodInfo* remove;
    const MethodInfo* raise;
    uint32_t token;
} Il2CppMetadataEventInfo;
typedef struct Il2CppInterfaceOffsetInfo
{
    const Il2CppType* interfaceType;
    int32_t offset;
} Il2CppInterfaceOffsetInfo;
typedef struct Il2CppGenericParameterInfo
{
    Il2CppMetadataGenericContainerHandle containerHandle;
    const char* name;
    uint16_t num;
    uint16_t flags;
} Il2CppGenericParameterInfo;
typedef enum Il2CppCallConvention
{
    IL2CPP_CALL_DEFAULT,
    IL2CPP_CALL_C,
    IL2CPP_CALL_STDCALL,
    IL2CPP_CALL_THISCALL,
    IL2CPP_CALL_FASTCALL,
    IL2CPP_CALL_VARARG
} Il2CppCallConvention;
typedef enum Il2CppCharSet
{
    CHARSET_ANSI,
    CHARSET_UNICODE,
    CHARSET_NOT_SPECIFIED
} Il2CppCharSet;
typedef struct Il2CppHString__
{
    int unused;
} Il2CppHString__;
typedef Il2CppHString__* Il2CppHString;
typedef struct Il2CppHStringHeader
{
    union
    {
        void* Reserved1;
        char Reserved2[24];
    } Reserved;
} Il2CppHStringHeader;
typedef struct Il2CppGuid
{
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
} Il2CppGuid;
typedef struct Il2CppSafeArrayBound
{
    uint32_t element_count;
    int32_t lower_bound;
} Il2CppSafeArrayBound;
typedef struct Il2CppSafeArray
{
    uint16_t dimension_count;
    uint16_t features;
    uint32_t element_size;
    uint32_t lock_count;
    void* data;
    Il2CppSafeArrayBound bounds[1];
} Il2CppSafeArray;
typedef struct Il2CppWin32Decimal
{
    uint16_t reserved;
    union
    {
        struct
        {
            uint8_t scale;
            uint8_t sign;
        } s;
        uint16_t signscale;
    } u;
    uint32_t hi32;
    union
    {
        struct
        {
            uint32_t lo32;
            uint32_t mid32;
        } s2;
        uint64_t lo64;
    } u2;
} Il2CppWin32Decimal;
typedef int16_t IL2CPP_VARIANT_BOOL;
typedef enum Il2CppVarType
{
    IL2CPP_VT_EMPTY = 0,
    IL2CPP_VT_NULL = 1,
    IL2CPP_VT_I2 = 2,
    IL2CPP_VT_I4 = 3,
    IL2CPP_VT_R4 = 4,
    IL2CPP_VT_R8 = 5,
    IL2CPP_VT_CY = 6,
    IL2CPP_VT_DATE = 7,
    IL2CPP_VT_BSTR = 8,
    IL2CPP_VT_DISPATCH = 9,
    IL2CPP_VT_ERROR = 10,
    IL2CPP_VT_BOOL = 11,
    IL2CPP_VT_VARIANT = 12,
    IL2CPP_VT_UNKNOWN = 13,
    IL2CPP_VT_DECIMAL = 14,
    IL2CPP_VT_I1 = 16,
    IL2CPP_VT_UI1 = 17,
    IL2CPP_VT_UI2 = 18,
    IL2CPP_VT_UI4 = 19,
    IL2CPP_VT_I8 = 20,
    IL2CPP_VT_UI8 = 21,
    IL2CPP_VT_INT = 22,
    IL2CPP_VT_UINT = 23,
    IL2CPP_VT_VOID = 24,
    IL2CPP_VT_HRESULT = 25,
    IL2CPP_VT_PTR = 26,
    IL2CPP_VT_SAFEARRAY = 27,
    IL2CPP_VT_CARRAY = 28,
    IL2CPP_VT_USERDEFINED = 29,
    IL2CPP_VT_LPSTR = 30,
    IL2CPP_VT_LPWSTR = 31,
    IL2CPP_VT_RECORD = 36,
    IL2CPP_VT_INT_PTR = 37,
    IL2CPP_VT_UINT_PTR = 38,
    IL2CPP_VT_FILETIME = 64,
    IL2CPP_VT_BLOB = 65,
    IL2CPP_VT_STREAM = 66,
    IL2CPP_VT_STORAGE = 67,
    IL2CPP_VT_STREAMED_OBJECT = 68,
    IL2CPP_VT_STORED_OBJECT = 69,
    IL2CPP_VT_BLOB_OBJECT = 70,
    IL2CPP_VT_CF = 71,
    IL2CPP_VT_CLSID = 72,
    IL2CPP_VT_VERSIONED_STREAM = 73,
    IL2CPP_VT_BSTR_BLOB = 0xfff,
    IL2CPP_VT_VECTOR = 0x1000,
    IL2CPP_VT_ARRAY = 0x2000,
    IL2CPP_VT_BYREF = 0x4000,
    IL2CPP_VT_RESERVED = 0x8000,
    IL2CPP_VT_ILLEGAL = 0xffff,
    IL2CPP_VT_ILLEGALMASKED = 0xfff,
    IL2CPP_VT_TYPEMASK = 0xfff,
} Il2CppVarType;
typedef struct Il2CppVariant Il2CppVariant;
typedef struct Il2CppIUnknown Il2CppIUnknown;
typedef struct Il2CppVariant
{
    union
    {
        struct __tagVARIANT
        {
            uint16_t type;
            uint16_t reserved1;
            uint16_t reserved2;
            uint16_t reserved3;
            union
            {
                int64_t llVal;
                int32_t lVal;
                uint8_t bVal;
                int16_t iVal;
                float fltVal;
                double dblVal;
                IL2CPP_VARIANT_BOOL boolVal;
                int32_t scode;
                int64_t cyVal;
                double date;
                Il2CppChar* bstrVal;
                Il2CppIUnknown* punkVal;
                void* pdispVal;
                Il2CppSafeArray* parray;
                uint8_t* pbVal;
                int16_t* piVal;
                int32_t* plVal;
                int64_t* pllVal;
                float* pfltVal;
                double* pdblVal;
                IL2CPP_VARIANT_BOOL* pboolVal;
                int32_t* pscode;
                int64_t* pcyVal;
                double* pdate;
                Il2CppChar* pbstrVal;
                Il2CppIUnknown** ppunkVal;
                void** ppdispVal;
                Il2CppSafeArray** pparray;
                struct Il2CppVariant* pvarVal;
                void* byref;
                char cVal;
                uint16_t uiVal;
                uint32_t ulVal;
                uint64_t ullVal;
                int intVal;
                unsigned int uintVal;
                Il2CppWin32Decimal* pdecVal;
                char* pcVal;
                uint16_t* puiVal;
                uint32_t* pulVal;
                uint64_t* pullVal;
                int* pintVal;
                unsigned int* puintVal;
                struct __tagBRECORD
                {
                    void* pvRecord;
                    void* pRecInfo;
                } n4;
            } n3;
        } n2;
        Il2CppWin32Decimal decVal;
    } n1;
} Il2CppVariant;
typedef struct Il2CppFileTime
{
    uint32_t low;
    uint32_t high;
} Il2CppFileTime;
typedef struct Il2CppStatStg
{
    Il2CppChar* name;
    uint32_t type;
    uint64_t size;
    Il2CppFileTime mtime;
    Il2CppFileTime ctime;
    Il2CppFileTime atime;
    uint32_t mode;
    uint32_t locks;
    Il2CppGuid clsid;
    uint32_t state;
    uint32_t reserved;
} Il2CppStatStg;
typedef enum Il2CppWindowsRuntimeTypeKind
{
    kTypeKindPrimitive = 0,
    kTypeKindMetadata,
    kTypeKindCustom
} Il2CppWindowsRuntimeTypeKind;
typedef struct Il2CppWindowsRuntimeTypeName
{
    Il2CppHString typeName;
    enum Il2CppWindowsRuntimeTypeKind typeKind;
} Il2CppWindowsRuntimeTypeName;
typedef void (*PInvokeMarshalToNativeFunc)(void* managedStructure, void* marshaledStructure);
typedef void (*PInvokeMarshalFromNativeFunc)(void* marshaledStructure, void* managedStructure);
typedef void (*PInvokeMarshalCleanupFunc)(void* marshaledStructure);
typedef struct Il2CppIUnknown* (*CreateCCWFunc)(Il2CppObject* obj);
typedef struct Il2CppInteropData
{
    Il2CppMethodPointer delegatePInvokeWrapperFunction;
    PInvokeMarshalToNativeFunc pinvokeMarshalToNativeFunction;
    PInvokeMarshalFromNativeFunc pinvokeMarshalFromNativeFunction;
    PInvokeMarshalCleanupFunc pinvokeMarshalCleanupFunction;
    CreateCCWFunc createCCWFunction;
    const Il2CppGuid* guid;
    const Il2CppType* type;
} Il2CppInteropData;
typedef struct Il2CppCodeGenModule Il2CppCodeGenModule;
typedef struct Il2CppMetadataRegistration Il2CppMetadataRegistration;
typedef struct Il2CppCodeRegistration Il2CppCodeRegistration;
typedef struct Il2CppClass Il2CppClass;
typedef struct Il2CppGuid Il2CppGuid;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppAppDomain Il2CppAppDomain;
typedef struct Il2CppAppDomainSetup Il2CppAppDomainSetup;
typedef struct Il2CppDelegate Il2CppDelegate;
typedef struct Il2CppAppContext Il2CppAppContext;
typedef struct Il2CppNameToTypeHandleHashTable Il2CppNameToTypeHandleHashTable;
typedef struct Il2CppCodeGenModule Il2CppCodeGenModule;
typedef struct Il2CppMetadataRegistration Il2CppMetadataRegistration;
typedef struct Il2CppCodeRegistration Il2CppCodeRegistration;
typedef struct VirtualInvokeData
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
} VirtualInvokeData;
typedef enum Il2CppTypeNameFormat
{
    IL2CPP_TYPE_NAME_FORMAT_IL,
    IL2CPP_TYPE_NAME_FORMAT_REFLECTION,
    IL2CPP_TYPE_NAME_FORMAT_FULL_NAME,
    IL2CPP_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED
} Il2CppTypeNameFormat;
typedef struct Il2CppDefaults
{
    Il2CppImage* corlib;
    Il2CppClass* object_class;
    Il2CppClass* byte_class;
    Il2CppClass* void_class;
    Il2CppClass* boolean_class;
    Il2CppClass* sbyte_class;
    Il2CppClass* int16_class;
    Il2CppClass* uint16_class;
    Il2CppClass* int32_class;
    Il2CppClass* uint32_class;
    Il2CppClass* int_class;
    Il2CppClass* uint_class;
    Il2CppClass* int64_class;
    Il2CppClass* uint64_class;
    Il2CppClass* single_class;
    Il2CppClass* double_class;
    Il2CppClass* char_class;
    Il2CppClass* string_class;
    Il2CppClass* enum_class;
    Il2CppClass* array_class;
    Il2CppClass* delegate_class;
    Il2CppClass* multicastdelegate_class;
    Il2CppClass* asyncresult_class;
    Il2CppClass* manualresetevent_class;
    Il2CppClass* typehandle_class;
    Il2CppClass* fieldhandle_class;
    Il2CppClass* methodhandle_class;
    Il2CppClass* systemtype_class;
    Il2CppClass* monotype_class;
    Il2CppClass* exception_class;
    Il2CppClass* threadabortexception_class;
    Il2CppClass* thread_class;
    Il2CppClass* internal_thread_class;
    Il2CppClass* appdomain_class;
    Il2CppClass* appdomain_setup_class;
    Il2CppClass* field_info_class;
    Il2CppClass* method_info_class;
    Il2CppClass* property_info_class;
    Il2CppClass* event_info_class;
    Il2CppClass* mono_event_info_class;
    Il2CppClass* stringbuilder_class;
    Il2CppClass* stack_frame_class;
    Il2CppClass* stack_trace_class;
    Il2CppClass* marshal_class;
    Il2CppClass* typed_reference_class;
    Il2CppClass* marshalbyrefobject_class;
    Il2CppClass* generic_ilist_class;
    Il2CppClass* generic_icollection_class;
    Il2CppClass* generic_ienumerable_class;
    Il2CppClass* generic_ireadonlylist_class;
    Il2CppClass* generic_ireadonlycollection_class;
    Il2CppClass* runtimetype_class;
    Il2CppClass* generic_nullable_class;
    Il2CppClass* il2cpp_com_object_class;
    Il2CppClass* attribute_class;
    Il2CppClass* customattribute_data_class;
    Il2CppClass* version;
    Il2CppClass* culture_info;
    Il2CppClass* async_call_class;
    Il2CppClass* assembly_class;
    Il2CppClass* mono_assembly_class;
    Il2CppClass* assembly_name_class;
    Il2CppClass* mono_field_class;
    Il2CppClass* mono_method_class;
    Il2CppClass* mono_method_info_class;
    Il2CppClass* mono_property_info_class;
    Il2CppClass* parameter_info_class;
    Il2CppClass* mono_parameter_info_class;
    Il2CppClass* module_class;
    Il2CppClass* pointer_class;
    Il2CppClass* system_exception_class;
    Il2CppClass* argument_exception_class;
    Il2CppClass* wait_handle_class;
    Il2CppClass* safe_handle_class;
    Il2CppClass* sort_key_class;
    Il2CppClass* dbnull_class;
    Il2CppClass* error_wrapper_class;
    Il2CppClass* missing_class;
    Il2CppClass* value_type_class;
    Il2CppClass* threadpool_wait_callback_class;
    MethodInfo* threadpool_perform_wait_callback_method;
    Il2CppClass* mono_method_message_class;
    Il2CppClass* ireference_class;
    Il2CppClass* ireferencearray_class;
    Il2CppClass* ikey_value_pair_class;
    Il2CppClass* key_value_pair_class;
    Il2CppClass* windows_foundation_uri_class;
    Il2CppClass* windows_foundation_iuri_runtime_class_class;
    Il2CppClass* system_uri_class;
    Il2CppClass* system_guid_class;
    Il2CppClass* sbyte_shared_enum;
    Il2CppClass* int16_shared_enum;
    Il2CppClass* int32_shared_enum;
    Il2CppClass* int64_shared_enum;
    Il2CppClass* byte_shared_enum;
    Il2CppClass* uint16_shared_enum;
    Il2CppClass* uint32_shared_enum;
    Il2CppClass* uint64_shared_enum;
} Il2CppDefaults;
extern Il2CppDefaults il2cpp_defaults;
typedef struct Il2CppClass Il2CppClass;
typedef struct MethodInfo MethodInfo;
typedef struct FieldInfo FieldInfo;
typedef struct Il2CppObject Il2CppObject;
typedef struct MemberInfo MemberInfo;
typedef struct CustomAttributesCache
{
    int count;
    Il2CppObject** attributes;
} CustomAttributesCache;
typedef void (*CustomAttributesCacheGenerator)(CustomAttributesCache*);
typedef struct FieldInfo
{
    const char* name;
    const Il2CppType* type;
    Il2CppClass* parent;
    int32_t offset;
    uint32_t token;
} FieldInfo;
typedef struct PropertyInfo
{
    Il2CppClass* parent;
    const char* name;
    const MethodInfo* get;
    const MethodInfo* set;
    uint32_t attrs;
    uint32_t token;
} PropertyInfo;
typedef struct EventInfo
{
    const char* name;
    const Il2CppType* eventType;
    Il2CppClass* parent;
    const MethodInfo* add;
    const MethodInfo* remove;
    const MethodInfo* raise;
    uint32_t token;
} EventInfo;
typedef struct ParameterInfo
{
    const char* name;
    int32_t position;
    uint32_t token;
    const Il2CppType* parameter_type;
} ParameterInfo;
typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**, void*);
typedef enum MethodVariableKind
{
    kMethodVariableKind_This,
    kMethodVariableKind_Parameter,
    kMethodVariableKind_LocalVariable
} MethodVariableKind;
typedef enum SequencePointKind
{
    kSequencePointKind_Normal,
    kSequencePointKind_StepOut
} SequencePointKind;
typedef struct Il2CppMethodExecutionContextInfo
{
    TypeIndex typeIndex;
    int32_t nameIndex;
    int32_t scopeIndex;
} Il2CppMethodExecutionContextInfo;
typedef struct Il2CppMethodExecutionContextInfoIndex
{
    int32_t startIndex;
    int32_t count;
} Il2CppMethodExecutionContextInfoIndex;
typedef struct Il2CppMethodScope
{
    int32_t startOffset;
    int32_t endOffset;
} Il2CppMethodScope;
typedef struct Il2CppMethodHeaderInfo
{
    int32_t code_size;
    int32_t startScope;
    int32_t numScopes;
} Il2CppMethodHeaderInfo;
typedef struct Il2CppSequencePointSourceFile
{
    const char* file;
    uint8_t hash[16];
} Il2CppSequencePointSourceFile;
typedef struct Il2CppTypeSourceFilePair
{
    TypeDefinitionIndex __klassIndex;
    int32_t sourceFileIndex;
} Il2CppTypeSourceFilePair;
typedef struct Il2CppSequencePoint
{
    MethodIndex __methodDefinitionIndex;
    int32_t sourceFileIndex;
    int32_t lineStart, lineEnd;
    int32_t columnStart, columnEnd;
    int32_t ilOffset;
    SequencePointKind kind;
    int32_t isActive;
    int32_t id;
} Il2CppSequencePoint;
typedef struct Il2CppCatchPoint
{
    MethodIndex __methodDefinitionIndex;
    TypeIndex catchTypeIndex;
    int32_t ilOffset;
    int32_t tryId;
    int32_t parentTryId;
} Il2CppCatchPoint;
typedef struct Il2CppDebuggerMetadataRegistration
{
    Il2CppMethodExecutionContextInfo* methodExecutionContextInfos;
    Il2CppMethodExecutionContextInfoIndex* methodExecutionContextInfoIndexes;
    Il2CppMethodScope* methodScopes;
    Il2CppMethodHeaderInfo* methodHeaderInfos;
    Il2CppSequencePointSourceFile* sequencePointSourceFiles;
    int32_t numSequencePoints;
    Il2CppSequencePoint* sequencePoints;
    int32_t numCatchPoints;
    Il2CppCatchPoint* catchPoints;
    int32_t numTypeSourceFileEntries;
    Il2CppTypeSourceFilePair* typeSourceFiles;
    const char** methodExecutionContextInfoStrings;
} Il2CppDebuggerMetadataRegistration;
typedef union Il2CppRGCTXData
{
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppType* type;
    Il2CppClass* klass;
} Il2CppRGCTXData;
typedef struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    InvokerMethod invoker_method;
    const char* name;
    Il2CppClass* klass;
    const Il2CppType* return_type;
    const ParameterInfo* parameters;
    union
    {
        const Il2CppRGCTXData* rgctx_data;
        Il2CppMetadataMethodDefinitionHandle methodMetadataHandle;
    } Il2CppVariant;
    union
    {
        const Il2CppGenericMethod* genericMethod;
        Il2CppMetadataGenericContainerHandle genericContainerHandle;
    };
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t is_generic : 1;
    uint8_t is_inflated : 1;
    uint8_t wrapper_type : 1;
    uint8_t is_marshaled_from_native : 1;
} MethodInfo;
typedef struct Il2CppRuntimeInterfaceOffsetPair
{
    Il2CppClass* interfaceType;
    int32_t offset;
} Il2CppRuntimeInterfaceOffsetPair;
typedef struct Il2CppClass
{
    const Il2CppImage* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    Il2CppGenericClass* generic_class;
    Il2CppMetadataTypeHandle typeMetadataHandle;
    const Il2CppInteropData* interopData;
    Il2CppClass* klass;
    FieldInfo* fields;
    const EventInfo* events;
    const PropertyInfo* properties;
    const MethodInfo** methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
    void* static_fields;
    const Il2CppRGCTXData* rgctx_data;
    struct Il2CppClass** typeHierarchy;
    void* unity_user_data;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    __declspec(align(8)) size_t cctor_thread;
    Il2CppMetadataGenericContainerHandle genericContainerHandle;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t initialized_and_no_error : 1;
    uint8_t valuetype : 1;
    uint8_t initialized : 1;
    uint8_t enumtype : 1;
    uint8_t is_generic : 1;
    uint8_t has_references : 1;
    uint8_t init_pending : 1;
    uint8_t size_init_pending : 1;
    uint8_t size_inited : 1;
    uint8_t has_finalize : 1;
    uint8_t has_cctor : 1;
    uint8_t is_blittable : 1;
    uint8_t is_import_or_windows_runtime : 1;
    uint8_t is_vtable_initialized : 1;
    uint8_t has_initialization_error : 1;
    VirtualInvokeData vtable[32];
} Il2CppClass;

typedef struct Il2CppClass_0
{
    const Il2CppImage* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    Il2CppGenericClass* generic_class;
    Il2CppMetadataTypeHandle typeMetadataHandle;
    const Il2CppInteropData* interopData;
    Il2CppClass* klass;
    FieldInfo* fields;
    const EventInfo* events;
    const PropertyInfo* properties;
    const MethodInfo** methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
} Il2CppClass_0;

typedef struct Il2CppClass_1
{
    struct Il2CppClass** typeHierarchy;
    void* unity_user_data;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
#ifdef IS_32BIT
    uint32_t cctor_thread;
#else
    __declspec(align(8)) size_t cctor_thread;
#endif
    Il2CppMetadataGenericContainerHandle genericContainerHandle;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t initialized_and_no_error : 1;
    uint8_t valuetype : 1;
    uint8_t initialized : 1;
    uint8_t enumtype : 1;
    uint8_t is_generic : 1;
    uint8_t has_references : 1;
    uint8_t init_pending : 1;
    uint8_t size_init_pending : 1;
    uint8_t size_inited : 1;
    uint8_t has_finalize : 1;
    uint8_t has_cctor : 1;
    uint8_t is_blittable : 1;
    uint8_t is_import_or_windows_runtime : 1;
    uint8_t is_vtable_initialized : 1;
    uint8_t has_initialization_error : 1;
} Il2CppClass_1;

typedef struct __declspec(align(8)) Il2CppClass_Merged
{
    struct Il2CppClass_0 _0;
    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
    void* static_fields;
    const Il2CppRGCTXData* rgctx_data;
    struct Il2CppClass_1 _1;
    VirtualInvokeData vtable[32];
} Il2CppClass_Merged;

typedef struct Il2CppTypeDefinitionSizes
{
    uint32_t instance_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
} Il2CppTypeDefinitionSizes;
typedef struct Il2CppDomain
{
    Il2CppAppDomain* domain;
    Il2CppAppDomainSetup* setup;
    Il2CppAppContext* default_context;
    const char* friendly_name;
    uint32_t domain_id;
    volatile int threadpool_jobs;
    void* agent_info;
} Il2CppDomain;
typedef struct Il2CppAssemblyName
{
    const char* name;
    const char* culture;
    const uint8_t* public_key;
    uint32_t hash_alg;
    int32_t hash_len;
    uint32_t flags;
    int32_t major;
    int32_t minor;
    int32_t build;
    int32_t revision;
    uint8_t public_key_token[8];
} Il2CppAssemblyName;
typedef struct Il2CppImage
{
    const char* name;
    const char* nameNoExt;
    Il2CppAssembly* assembly;
    uint32_t typeCount;
    uint32_t exportedTypeCount;
    uint32_t customAttributeCount;
    Il2CppMetadataImageHandle metadataHandle;
    Il2CppNameToTypeHandleHashTable* nameToClassHashTable;
    const Il2CppCodeGenModule* codeGenModule;
    uint32_t token;
    uint8_t dynamic;
} Il2CppImage;
typedef struct Il2CppAssembly
{
    Il2CppImage* image;
    uint32_t token;
    int32_t referencedAssemblyStart;
    int32_t referencedAssemblyCount;
    Il2CppAssemblyName aname;
} Il2CppAssembly;
typedef struct Il2CppCodeGenOptions
{
    uint8_t enablePrimitiveValueTypeGenericSharing;
    int maximumRuntimeGenericDepth;
} Il2CppCodeGenOptions;
typedef struct Il2CppRange
{
    int32_t start;
    int32_t length;
} Il2CppRange;
typedef struct Il2CppTokenRangePair
{
    uint32_t token;
    Il2CppRange range;
} Il2CppTokenRangePair;
typedef struct Il2CppTokenIndexMethodTuple
{
    uint32_t token;
    int32_t index;
    void** method;
    uint32_t __genericMethodIndex;
} Il2CppTokenIndexMethodTuple;
typedef struct Il2CppWindowsRuntimeFactoryTableEntry
{
    const Il2CppType* type;
    Il2CppMethodPointer createFactoryFunction;
} Il2CppWindowsRuntimeFactoryTableEntry;
typedef struct Il2CppCodeGenModule
{
    const char* moduleName;
    const uint32_t methodPointerCount;
    const Il2CppMethodPointer* methodPointers;
    const int32_t* invokerIndices;
    const uint32_t reversePInvokeWrapperCount;
    const Il2CppTokenIndexMethodTuple* reversePInvokeWrapperIndices;
    const uint32_t rgctxRangesCount;
    const Il2CppTokenRangePair* rgctxRanges;
    const uint32_t rgctxsCount;
    const Il2CppRGCTXDefinition* rgctxs;
    const Il2CppDebuggerMetadataRegistration* debuggerMetadata;
    const CustomAttributesCacheGenerator* customAttributeCacheGenerator;
    const Il2CppMethodPointer moduleInitializer;
    TypeDefinitionIndex* staticConstructorTypeIndices;
    const Il2CppMetadataRegistration* metadataRegistration;
    const Il2CppCodeRegistration* codeRegistaration;
} Il2CppCodeGenModule;
typedef struct Il2CppCodeRegistration
{
    uint32_t reversePInvokeWrapperCount;
    const Il2CppMethodPointer* reversePInvokeWrappers;
    uint32_t genericMethodPointersCount;
    const Il2CppMethodPointer* genericMethodPointers;
    uint32_t invokerPointersCount;
    const InvokerMethod* invokerPointers;
    uint32_t unresolvedVirtualCallCount;
    const Il2CppMethodPointer* unresolvedVirtualCallPointers;
    uint32_t interopDataCount;
    Il2CppInteropData* interopData;
    uint32_t windowsRuntimeFactoryCount;
    Il2CppWindowsRuntimeFactoryTableEntry* windowsRuntimeFactoryTable;
    uint32_t codeGenModulesCount;
    const Il2CppCodeGenModule** codeGenModules;
} Il2CppCodeRegistration;
typedef struct Il2CppMetadataRegistration
{
    int32_t genericClassesCount;
    Il2CppGenericClass* const* genericClasses;
    int32_t genericInstsCount;
    const Il2CppGenericInst* const* genericInsts;
    int32_t genericMethodTableCount;
    const Il2CppGenericMethodFunctionsDefinitions* genericMethodTable;
    int32_t typesCount;
    const Il2CppType* const* types;
    int32_t methodSpecsCount;
    const Il2CppMethodSpec* methodSpecs;
    FieldIndex fieldOffsetsCount;
    const int32_t** fieldOffsets;
    TypeDefinitionIndex typeDefinitionsSizesCount;
    const Il2CppTypeDefinitionSizes** typeDefinitionsSizes;
    const size_t metadataUsagesCount;
    void** const* metadataUsages;
} Il2CppMetadataRegistration;
typedef struct Il2CppPerfCounters
{
    uint32_t jit_methods;
    uint32_t jit_bytes;
    uint32_t jit_time;
    uint32_t jit_failures;
    uint32_t exceptions_thrown;
    uint32_t exceptions_filters;
    uint32_t exceptions_finallys;
    uint32_t exceptions_depth;
    uint32_t aspnet_requests_queued;
    uint32_t aspnet_requests;
    uint32_t gc_collections0;
    uint32_t gc_collections1;
    uint32_t gc_collections2;
    uint32_t gc_promotions0;
    uint32_t gc_promotions1;
    uint32_t gc_promotion_finalizers;
    uint32_t gc_gen0size;
    uint32_t gc_gen1size;
    uint32_t gc_gen2size;
    uint32_t gc_lossize;
    uint32_t gc_fin_survivors;
    uint32_t gc_num_handles;
    uint32_t gc_allocated;
    uint32_t gc_induced;
    uint32_t gc_time;
    uint32_t gc_total_bytes;
    uint32_t gc_committed_bytes;
    uint32_t gc_reserved_bytes;
    uint32_t gc_num_pinned;
    uint32_t gc_sync_blocks;
    uint32_t remoting_calls;
    uint32_t remoting_channels;
    uint32_t remoting_proxies;
    uint32_t remoting_classes;
    uint32_t remoting_objects;
    uint32_t remoting_contexts;
    uint32_t loader_classes;
    uint32_t loader_total_classes;
    uint32_t loader_appdomains;
    uint32_t loader_total_appdomains;
    uint32_t loader_assemblies;
    uint32_t loader_total_assemblies;
    uint32_t loader_failures;
    uint32_t loader_bytes;
    uint32_t loader_appdomains_uloaded;
    uint32_t thread_contentions;
    uint32_t thread_queue_len;
    uint32_t thread_queue_max;
    uint32_t thread_num_logical;
    uint32_t thread_num_physical;
    uint32_t thread_cur_recognized;
    uint32_t thread_num_recognized;
    uint32_t interop_num_ccw;
    uint32_t interop_num_stubs;
    uint32_t interop_num_marshals;
    uint32_t security_num_checks;
    uint32_t security_num_link_checks;
    uint32_t security_time;
    uint32_t security_depth;
    uint32_t unused;
    uint64_t threadpool_workitems;
    uint64_t threadpool_ioworkitems;
    unsigned int threadpool_threads;
    unsigned int threadpool_iothreads;
} Il2CppPerfCounters;
typedef struct Il2CppClass Il2CppClass;
typedef struct MethodInfo MethodInfo;
typedef struct PropertyInfo PropertyInfo;
typedef struct FieldInfo FieldInfo;
typedef struct EventInfo EventInfo;
typedef struct Il2CppType Il2CppType;
typedef struct Il2CppAssembly Il2CppAssembly;
typedef struct Il2CppException Il2CppException;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppDomain Il2CppDomain;
typedef struct Il2CppString Il2CppString;
typedef struct Il2CppReflectionMethod Il2CppReflectionMethod;
typedef struct Il2CppAsyncCall Il2CppAsyncCall;
typedef struct Il2CppIUnknown Il2CppIUnknown;
typedef struct Il2CppWaitHandle Il2CppWaitHandle;
typedef struct MonitorData MonitorData;
typedef struct Il2CppReflectionAssembly Il2CppReflectionAssembly;
typedef Il2CppClass Il2CppVTable;
typedef struct Il2CppObject
{
    union
    {
        Il2CppClass* klass;
        Il2CppVTable* vtable;
    } Il2CppClass;
    void* monitor;
} Il2CppObject;
typedef int32_t il2cpp_array_lower_bound_t;
typedef struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
} Il2CppArrayBounds;
typedef struct Il2CppArray
{
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
} Il2CppArray;
typedef struct Il2CppArraySize
{
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    __declspec(align(8)) void* vector[32];
} Il2CppArraySize;
typedef struct Il2CppString
{
    Il2CppObject object;
    int32_t length;
    Il2CppChar chars[32];
} Il2CppString;
typedef struct Il2CppReflectionType
{
    Il2CppObject object;
    const Il2CppType* type;
} Il2CppReflectionType;
typedef struct Il2CppReflectionRuntimeType
{
    Il2CppReflectionType type;
    Il2CppObject* type_info;
    Il2CppObject* genericCache;
    Il2CppObject* serializationCtor;
} Il2CppReflectionRuntimeType;
typedef struct Il2CppReflectionMonoType
{
    Il2CppReflectionRuntimeType type;
} Il2CppReflectionMonoType;
typedef struct Il2CppReflectionEvent
{
    Il2CppObject object;
    Il2CppObject* cached_add_event;
} Il2CppReflectionEvent;
typedef struct Il2CppReflectionMonoEvent
{
    Il2CppReflectionEvent event;
    Il2CppReflectionType* reflectedType;
    const EventInfo* eventInfo;
} Il2CppReflectionMonoEvent;
typedef struct Il2CppReflectionMonoEventInfo
{
    Il2CppReflectionType* declaringType;
    Il2CppReflectionType* reflectedType;
    Il2CppString* name;
    Il2CppReflectionMethod* addMethod;
    Il2CppReflectionMethod* removeMethod;
    Il2CppReflectionMethod* raiseMethod;
    uint32_t eventAttributes;
    Il2CppArray* otherMethods;
} Il2CppReflectionMonoEventInfo;
typedef struct Il2CppReflectionField
{
    Il2CppObject object;
    Il2CppClass* klass;
    FieldInfo* field;
    Il2CppString* name;
    Il2CppReflectionType* type;
    uint32_t attrs;
} Il2CppReflectionField;
typedef struct Il2CppReflectionProperty
{
    Il2CppObject object;
    Il2CppClass* klass;
    const PropertyInfo* property;
} Il2CppReflectionProperty;
typedef struct Il2CppReflectionMethod
{
    Il2CppObject object;
    const MethodInfo* method;
    Il2CppString* name;
    Il2CppReflectionType* reftype;
} Il2CppReflectionMethod;
typedef struct Il2CppReflectionGenericMethod
{
    Il2CppReflectionMethod base;
} Il2CppReflectionGenericMethod;
typedef struct Il2CppMethodInfo
{
    Il2CppReflectionType* parent;
    Il2CppReflectionType* ret;
    uint32_t attrs;
    uint32_t implattrs;
    uint32_t callconv;
} Il2CppMethodInfo;
typedef struct Il2CppPropertyInfo
{
    Il2CppReflectionType* parent;
    Il2CppReflectionType* declaringType;
    Il2CppString* name;
    Il2CppReflectionMethod* get;
    Il2CppReflectionMethod* set;
    uint32_t attrs;
} Il2CppPropertyInfo;
typedef struct Il2CppReflectionParameter
{
    Il2CppObject object;
    Il2CppReflectionType* ClassImpl;
    Il2CppObject* DefaultValueImpl;
    Il2CppObject* MemberImpl;
    Il2CppString* NameImpl;
    int32_t PositionImpl;
    uint32_t AttrsImpl;
    Il2CppObject* MarshalAsImpl;
} Il2CppReflectionParameter;
typedef struct Il2CppReflectionModule
{
    Il2CppObject obj;
    const Il2CppImage* image;
    Il2CppReflectionAssembly* assembly;
    Il2CppString* fqname;
    Il2CppString* name;
    Il2CppString* scopename;
    uint8_t is_resource;
    uint32_t token;
} Il2CppReflectionModule;
typedef struct Il2CppReflectionAssemblyName
{
    Il2CppObject obj;
    Il2CppString* name;
    Il2CppString* codebase;
    int32_t major, minor, build, revision;
    Il2CppObject* cultureInfo;
    uint32_t flags;
    uint32_t hashalg;
    Il2CppObject* keypair;
    Il2CppArray* publicKey;
    Il2CppArray* keyToken;
    uint32_t versioncompat;
    Il2CppObject* version;
    uint32_t processor_architecture;
    uint32_t contentType;
} Il2CppReflectionAssemblyName;
typedef struct Il2CppReflectionAssembly
{
    Il2CppObject object;
    const Il2CppAssembly* assembly;
    Il2CppObject* resolve_event_holder;
    Il2CppObject* evidence;
    Il2CppObject* minimum;
    Il2CppObject* optional;
    Il2CppObject* refuse;
    Il2CppObject* granted;
    Il2CppObject* denied;
    uint8_t from_byte_array;
    Il2CppString* name;
} Il2CppReflectionAssembly;
typedef struct Il2CppReflectionMarshal
{
    Il2CppObject object;
    int32_t count;
    int32_t type;
    int32_t eltype;
    Il2CppString* guid;
    Il2CppString* mcookie;
    Il2CppString* marshaltype;
    Il2CppObject* marshaltyperef;
    int32_t param_num;
    uint8_t has_size;
} Il2CppReflectionMarshal;
typedef struct Il2CppReflectionPointer
{
    Il2CppObject object;
    void* data;
    Il2CppReflectionType* type;
} Il2CppReflectionPointer;
typedef struct Il2CppInternalThread
{
    Il2CppObject obj;
    int lock_thread_id;
    void* handle;
    void* native_handle;
    Il2CppArray* cached_culture_info;
    Il2CppChar* name;
    int name_len;
    uint32_t state;
    Il2CppObject* abort_exc;
    int abort_state_handle;
    uint64_t tid;
    intptr_t debugger_thread;
    void** static_data;
    void* runtime_thread_info;
    Il2CppObject* current_appcontext;
    Il2CppObject* root_domain_thread;
    Il2CppArray* _serialized_principal;
    int _serialized_principal_version;
    void* appdomain_refs;
    int32_t interruption_requested;
    void* synch_cs;
    uint8_t threadpool_thread;
    uint8_t thread_interrupt_requested;
    int stack_size;
    uint8_t apartment_state;
    int critical_region_level;
    int managed_id;
    uint32_t small_id;
    void* manage_callback;
    void* interrupt_on_stop;
    intptr_t flags;
    void* thread_pinning_ref;
    void* abort_protected_block_count;
    int32_t priority;
    void* owned_mutexes;
    void* suspended;
    int32_t self_suspended;
    size_t thread_state;
    size_t unused2;
    void* last;
} Il2CppInternalThread;
typedef struct Il2CppIOSelectorJob
{
    Il2CppObject object;
    int32_t operation;
    Il2CppObject* callback;
    Il2CppObject* state;
} Il2CppIOSelectorJob;
typedef enum
{
    Il2Cpp_CallType_Sync = 0,
    Il2Cpp_CallType_BeginInvoke = 1,
    Il2Cpp_CallType_EndInvoke = 2,
    Il2Cpp_CallType_OneWay = 3
} Il2CppCallType;
typedef struct Il2CppMethodMessage
{
    Il2CppObject obj;
    Il2CppReflectionMethod* method;
    Il2CppArray* args;
    Il2CppArray* names;
    Il2CppArray* arg_types;
    Il2CppObject* ctx;
    Il2CppObject* rval;
    Il2CppObject* exc;
    Il2CppAsyncResult* async_result;
    uint32_t call_type;
} Il2CppMethodMessage;
typedef struct Il2CppAppDomainSetup
{
    Il2CppObject object;
    Il2CppString* application_base;
    Il2CppString* application_name;
    Il2CppString* cache_path;
    Il2CppString* configuration_file;
    Il2CppString* dynamic_base;
    Il2CppString* license_file;
    Il2CppString* private_bin_path;
    Il2CppString* private_bin_path_probe;
    Il2CppString* shadow_copy_directories;
    Il2CppString* shadow_copy_files;
    uint8_t publisher_policy;
    uint8_t path_changed;
    int loader_optimization;
    uint8_t disallow_binding_redirects;
    uint8_t disallow_code_downloads;
    Il2CppObject* activation_arguments;
    Il2CppObject* domain_initializer;
    Il2CppObject* application_trust;
    Il2CppArray* domain_initializer_args;
    uint8_t disallow_appbase_probe;
    Il2CppArray* configuration_bytes;
    Il2CppArray* serialized_non_primitives;
} Il2CppAppDomainSetup;
typedef struct Il2CppThread
{
    Il2CppObject obj;
    Il2CppInternalThread* internal_thread;
    Il2CppObject* start_obj;
    Il2CppException* pending_exception;
    Il2CppObject* principal;
    int32_t principal_version;
    Il2CppDelegate* delegate;
    Il2CppObject* executionContext;
    uint8_t executionContextBelongsToOuterScope;
} Il2CppThread;
typedef struct Il2CppException
{
    Il2CppObject object;
    Il2CppString* className;
    Il2CppString* message;
    Il2CppObject* _data;
    Il2CppException* inner_ex;
    Il2CppString* _helpURL;
    Il2CppArray* trace_ips;
    Il2CppString* stack_trace;
    Il2CppString* remote_stack_trace;
    int remote_stack_index;
    Il2CppObject* _dynamicMethods;
    il2cpp_hresult_t hresult;
    Il2CppString* source;
    Il2CppObject* safeSerializationManager;
    Il2CppArray* captured_traces;
    Il2CppArray* native_trace_ips;
} Il2CppException;
typedef struct Il2CppSystemException
{
    Il2CppException base;
} Il2CppSystemException;
typedef struct Il2CppArgumentException
{
    Il2CppException base;
    Il2CppString* argName;
} Il2CppArgumentException;
typedef struct Il2CppTypedRef
{
    const Il2CppType* type;
    void* value;
    Il2CppClass* klass;
} Il2CppTypedRef;
typedef struct Il2CppDelegate
{
    Il2CppObject object;
    Il2CppMethodPointer method_ptr;
    InvokerMethod invoke_impl;
    Il2CppObject* target;
    const MethodInfo* method;
    void* delegate_trampoline;
    intptr_t extraArg;
    uint8_t** method_code;
    Il2CppReflectionMethod* method_info;
    Il2CppReflectionMethod* original_method_info;
    Il2CppObject* data;
    uint8_t method_is_virtual;
} Il2CppDelegate;
typedef struct Il2CppMulticastDelegate
{
    Il2CppDelegate delegate;
    Il2CppArray* delegates;
} Il2CppMulticastDelegate;
typedef struct Il2CppMarshalByRefObject
{
    Il2CppObject obj;
    Il2CppObject* identity;
} Il2CppMarshalByRefObject;
typedef struct Il2CppAppDomain
{
    Il2CppMarshalByRefObject mbr;
    Il2CppDomain* data;
} Il2CppAppDomain;
typedef struct Il2CppStackFrame
{
    Il2CppObject obj;
    int32_t il_offset;
    int32_t native_offset;
    uint64_t methodAddress;
    uint32_t methodIndex;
    Il2CppReflectionMethod* method;
    Il2CppString* filename;
    int32_t line;
    int32_t column;
    Il2CppString* internal_method_name;
} Il2CppStackFrame;
typedef struct Il2CppDateTimeFormatInfo
{
    Il2CppObject obj;
    Il2CppObject* CultureData;
    Il2CppString* Name;
    Il2CppString* LangName;
    Il2CppObject* CompareInfo;
    Il2CppObject* CultureInfo;
    Il2CppString* AMDesignator;
    Il2CppString* PMDesignator;
    Il2CppString* DateSeparator;
    Il2CppString* GeneralShortTimePattern;
    Il2CppString* GeneralLongTimePattern;
    Il2CppString* TimeSeparator;
    Il2CppString* MonthDayPattern;
    Il2CppString* DateTimeOffsetPattern;
    Il2CppObject* Calendar;
    uint32_t FirstDayOfWeek;
    uint32_t CalendarWeekRule;
    Il2CppString* FullDateTimePattern;
    Il2CppArray* AbbreviatedDayNames;
    Il2CppArray* ShortDayNames;
    Il2CppArray* DayNames;
    Il2CppArray* AbbreviatedMonthNames;
    Il2CppArray* MonthNames;
    Il2CppArray* GenitiveMonthNames;
    Il2CppArray* GenitiveAbbreviatedMonthNames;
    Il2CppArray* LeapYearMonthNames;
    Il2CppString* LongDatePattern;
    Il2CppString* ShortDatePattern;
    Il2CppString* YearMonthPattern;
    Il2CppString* LongTimePattern;
    Il2CppString* ShortTimePattern;
    Il2CppArray* YearMonthPatterns;
    Il2CppArray* ShortDatePatterns;
    Il2CppArray* LongDatePatterns;
    Il2CppArray* ShortTimePatterns;
    Il2CppArray* LongTimePatterns;
    Il2CppArray* EraNames;
    Il2CppArray* AbbrevEraNames;
    Il2CppArray* AbbrevEnglishEraNames;
    Il2CppArray* OptionalCalendars;
    uint8_t readOnly;
    int32_t FormatFlags;
    int32_t CultureID;
    uint8_t UseUserOverride;
    uint8_t UseCalendarInfo;
    int32_t DataItem;
    uint8_t IsDefaultCalendar;
    Il2CppArray* DateWords;
    Il2CppString* FullTimeSpanPositivePattern;
    Il2CppString* FullTimeSpanNegativePattern;
    Il2CppArray* dtfiTokenHash;
} Il2CppDateTimeFormatInfo;
typedef struct Il2CppNumberFormatInfo
{
    Il2CppObject obj;
    Il2CppArray* numberGroupSizes;
    Il2CppArray* currencyGroupSizes;
    Il2CppArray* percentGroupSizes;
    Il2CppString* positiveSign;
    Il2CppString* negativeSign;
    Il2CppString* numberDecimalSeparator;
    Il2CppString* numberGroupSeparator;
    Il2CppString* currencyGroupSeparator;
    Il2CppString* currencyDecimalSeparator;
    Il2CppString* currencySymbol;
    Il2CppString* ansiCurrencySymbol;
    Il2CppString* naNSymbol;
    Il2CppString* positiveInfinitySymbol;
    Il2CppString* negativeInfinitySymbol;
    Il2CppString* percentDecimalSeparator;
    Il2CppString* percentGroupSeparator;
    Il2CppString* percentSymbol;
    Il2CppString* perMilleSymbol;
    Il2CppArray* nativeDigits;
    int dataItem;
    int numberDecimalDigits;
    int currencyDecimalDigits;
    int currencyPositivePattern;
    int currencyNegativePattern;
    int numberNegativePattern;
    int percentPositivePattern;
    int percentNegativePattern;
    int percentDecimalDigits;
    int digitSubstitution;
    uint8_t readOnly;
    uint8_t useUserOverride;
    uint8_t isInvariant;
    uint8_t validForParseAsNumber;
    uint8_t validForParseAsCurrency;
} Il2CppNumberFormatInfo;
typedef struct Il2CppCultureData
{
    Il2CppObject obj;
    Il2CppString* AMDesignator;
    Il2CppString* PMDesignator;
    Il2CppString* TimeSeparator;
    Il2CppArray* LongTimePatterns;
    Il2CppArray* ShortTimePatterns;
    uint32_t FirstDayOfWeek;
    uint32_t CalendarWeekRule;
} Il2CppCultureData;
typedef struct Il2CppCalendarData
{
    Il2CppObject obj;
    Il2CppString* NativeName;
    Il2CppArray* ShortDatePatterns;
    Il2CppArray* YearMonthPatterns;
    Il2CppArray* LongDatePatterns;
    Il2CppString* MonthDayPattern;
    Il2CppArray* EraNames;
    Il2CppArray* AbbreviatedEraNames;
    Il2CppArray* AbbreviatedEnglishEraNames;
    Il2CppArray* DayNames;
    Il2CppArray* AbbreviatedDayNames;
    Il2CppArray* SuperShortDayNames;
    Il2CppArray* MonthNames;
    Il2CppArray* AbbreviatedMonthNames;
    Il2CppArray* GenitiveMonthNames;
    Il2CppArray* GenitiveAbbreviatedMonthNames;
} Il2CppCalendarData;
typedef struct Il2CppCultureInfo
{
    Il2CppObject obj;
    uint8_t is_read_only;
    int32_t lcid;
    int32_t parent_lcid;
    int32_t datetime_index;
    int32_t number_index;
    int32_t default_calendar_type;
    uint8_t use_user_override;
    Il2CppNumberFormatInfo* number_format;
    Il2CppDateTimeFormatInfo* datetime_format;
    Il2CppObject* textinfo;
    Il2CppString* name;
    Il2CppString* englishname;
    Il2CppString* nativename;
    Il2CppString* iso3lang;
    Il2CppString* iso2lang;
    Il2CppString* win3lang;
    Il2CppString* territory;
    Il2CppArray* native_calendar_names;
    Il2CppString* compareinfo;
    const void* text_info_data;
    int dataItem;
    Il2CppObject* calendar;
    Il2CppObject* parent_culture;
    uint8_t constructed;
    Il2CppArray* cached_serialized_form;
    Il2CppObject* cultureData;
    uint8_t isInherited;
} Il2CppCultureInfo;
typedef struct Il2CppRegionInfo
{
    Il2CppObject obj;
    int32_t geo_id;
    Il2CppString* iso2name;
    Il2CppString* iso3name;
    Il2CppString* win3name;
    Il2CppString* english_name;
    Il2CppString* native_name;
    Il2CppString* currency_symbol;
    Il2CppString* iso_currency_symbol;
    Il2CppString* currency_english_name;
    Il2CppString* currency_native_name;
} Il2CppRegionInfo;
typedef struct Il2CppSafeHandle
{
    Il2CppObject base;
    void* handle;
    int state;
    uint8_t owns_handle;
    uint8_t fullyInitialized;
} Il2CppSafeHandle;
typedef struct Il2CppStringBuilder Il2CppStringBuilder;
typedef struct Il2CppStringBuilder
{
    Il2CppObject object;
    Il2CppArray* chunkChars;
    Il2CppStringBuilder* chunkPrevious;
    int chunkLength;
    int chunkOffset;
    int maxCapacity;
} Il2CppStringBuilder;
typedef struct Il2CppSocketAddress
{
    Il2CppObject base;
    int m_Size;
    Il2CppArray* data;
    uint8_t m_changed;
    int m_hash;
} Il2CppSocketAddress;
typedef struct Il2CppSortKey
{
    Il2CppObject base;
    Il2CppString* str;
    Il2CppArray* key;
    int32_t options;
    int32_t lcid;
} Il2CppSortKey;
typedef struct Il2CppErrorWrapper
{
    Il2CppObject base;
    int32_t errorCode;
} Il2CppErrorWrapper;
typedef struct Il2CppAsyncResult
{
    Il2CppObject base;
    Il2CppObject* async_state;
    Il2CppWaitHandle* handle;
    Il2CppDelegate* async_delegate;
    void* data;
    Il2CppAsyncCall* object_data;
    uint8_t sync_completed;
    uint8_t completed;
    uint8_t endinvoke_called;
    Il2CppObject* async_callback;
    Il2CppObject* execution_context;
    Il2CppObject* original_context;
} Il2CppAsyncResult;
typedef struct Il2CppAsyncCall
{
    Il2CppObject base;
    Il2CppMethodMessage* msg;
    MethodInfo* cb_method;
    Il2CppDelegate* cb_target;
    Il2CppObject* state;
    Il2CppObject* res;
    Il2CppArray* out_args;
} Il2CppAsyncCall;
typedef struct Il2CppExceptionWrapper Il2CppExceptionWrapper;
typedef struct Il2CppExceptionWrapper
{
    Il2CppException* ex;
} Il2CppExceptionWrapper;
typedef struct Il2CppIOAsyncResult
{
    Il2CppObject base;
    Il2CppDelegate* callback;
    Il2CppObject* state;
    Il2CppWaitHandle* wait_handle;
    uint8_t completed_synchronously;
    uint8_t completed;
} Il2CppIOAsyncResult;
typedef struct Il2CppSocketAsyncResult
{
    Il2CppIOAsyncResult base;
    Il2CppObject* socket;
    int32_t operation;
    Il2CppException* delayedException;
    Il2CppObject* endPoint;
    Il2CppArray* buffer;
    int32_t offset;
    int32_t size;
    int32_t socket_flags;
    Il2CppObject* acceptSocket;
    Il2CppArray* addresses;
    int32_t port;
    Il2CppObject* buffers;
    uint8_t reuseSocket;
    int32_t currentAddress;
    Il2CppObject* acceptedSocket;
    int32_t total;
    int32_t error;
    int32_t endCalled;
} Il2CppSocketAsyncResult;
typedef enum Il2CppResourceLocation
{
    IL2CPP_RESOURCE_LOCATION_EMBEDDED = 1,
    IL2CPP_RESOURCE_LOCATION_ANOTHER_ASSEMBLY = 2,
    IL2CPP_RESOURCE_LOCATION_IN_MANIFEST = 4
} Il2CppResourceLocation;
typedef struct Il2CppManifestResourceInfo
{
    Il2CppObject object;
    Il2CppReflectionAssembly* assembly;
    Il2CppString* filename;
    uint32_t location;
} Il2CppManifestResourceInfo;
typedef struct Il2CppAppContext
{
    Il2CppObject obj;
    int32_t domain_id;
    int32_t context_id;
    void* static_data;
} Il2CppAppContext;
typedef struct Il2CppDecimal
{
    uint16_t reserved;
    union
    {
        struct
        {
            uint8_t scale;
            uint8_t sign;
        } u;
        uint16_t signscale;
    } u;
    uint32_t Hi32;
    union
    {
        struct
        {
            uint32_t Lo32;
            uint32_t Mid32;
        } v;
        uint64_t Lo64;
    } v;
} Il2CppDecimal;
typedef struct Il2CppDouble
{
    uint32_t mantLo : 32;
    uint32_t mantHi : 20;
    uint32_t exp : 11;
    uint32_t sign : 1;
} Il2CppDouble;
typedef union Il2CppDouble_double
{
    Il2CppDouble s;
    double d;
} Il2CppDouble_double;
typedef enum Il2CppDecimalCompareResult
{
    IL2CPP_DECIMAL_CMP_LT = -1,
    IL2CPP_DECIMAL_CMP_EQ,
    IL2CPP_DECIMAL_CMP_GT
} Il2CppDecimalCompareResult;
typedef struct Il2CppSingle
{
    uint32_t mant : 23;
    uint32_t exp : 8;
    uint32_t sign : 1;
} Il2CppSingle;
typedef union Il2CppSingle_float
{
    Il2CppSingle s;
    float f;
} Il2CppSingle_float;
#pragma endregion


// ******************************************************************************
// * Game types
// ******************************************************************************
#pragma warning(disable : 4369)
#pragma warning(disable : 4309)
#pragma warning(disable : 4359)
#if !defined(_GHIDRA_) && !defined(_IDA_)
namespace app
{
#endif

#pragma region Object
    struct Object
    {
        struct Object__Class* klass;
        void* monitor;
    };

    struct Object__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Object__StaticFields
    {
    };

    struct Object__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Object__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Object__VTable vtable;
    };

#pragma endregion

#pragma region Type
    struct RuntimeTypeHandle
    {
        void* value;
    };

    struct __declspec(align(4)) Type__Fields
    {
        struct RuntimeTypeHandle _impl;
    };

    struct Type
    {
        struct Type__Class* klass;
        void* monitor;
        struct Type__Fields fields;
    };

    struct Type__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData GetCustomAttributes;
        VirtualInvokeData GetCustomAttributes_1;
        VirtualInvokeData IsDefined;
        VirtualInvokeData get_MemberType;
        VirtualInvokeData __unknown;
        VirtualInvokeData get_DeclaringType;
        VirtualInvokeData get_ReflectedType;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData GetCustomAttributesData;
        VirtualInvokeData get_MetadataToken;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData get_DeclaringMethod;
        VirtualInvokeData MakePointerType;
        VirtualInvokeData MakeByRefType;
        VirtualInvokeData MakeArrayType;
        VirtualInvokeData MakeArrayType_1;
        VirtualInvokeData GetTypeCodeImpl;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData __unknown_6;
        VirtualInvokeData InvokeMember;
        VirtualInvokeData __unknown_7;
        VirtualInvokeData get_TypeHandle;
        VirtualInvokeData __unknown_8;
        VirtualInvokeData __unknown_9;
        VirtualInvokeData __unknown_10;
        VirtualInvokeData GetArrayRank;
        VirtualInvokeData __unknown_11;
        VirtualInvokeData GetConstructor;
        VirtualInvokeData GetConstructor_1;
        VirtualInvokeData GetConstructor_2;
        VirtualInvokeData __unknown_12;
        VirtualInvokeData GetConstructors;
        VirtualInvokeData __unknown_13;
        VirtualInvokeData GetMethod;
        VirtualInvokeData GetMethod_1;
        VirtualInvokeData GetMethod_2;
        VirtualInvokeData GetMethod_3;
        VirtualInvokeData __unknown_14;
        VirtualInvokeData GetMethods;
        VirtualInvokeData __unknown_15;
        VirtualInvokeData __unknown_16;
        VirtualInvokeData GetField;
        VirtualInvokeData GetFields;
        VirtualInvokeData __unknown_17;
        VirtualInvokeData __unknown_18;
        VirtualInvokeData FindInterfaces;
        VirtualInvokeData GetEvent;
        VirtualInvokeData __unknown_19;
        VirtualInvokeData __unknown_20;
        VirtualInvokeData GetProperty;
        VirtualInvokeData GetProperty_1;
        VirtualInvokeData GetProperty_2;
        VirtualInvokeData GetProperty_3;
        VirtualInvokeData GetProperty_4;
        VirtualInvokeData __unknown_21;
        VirtualInvokeData __unknown_22;
        VirtualInvokeData GetProperties;
        VirtualInvokeData GetNestedType;
        VirtualInvokeData __unknown_23;
        VirtualInvokeData GetMember;
        VirtualInvokeData GetMember_1;
        VirtualInvokeData GetMember_2;
        VirtualInvokeData __unknown_24;
        VirtualInvokeData get_Attributes;
        VirtualInvokeData get_GenericParameterAttributes;
        VirtualInvokeData get_IsNotPublic;
        VirtualInvokeData get_IsPublic;
        VirtualInvokeData get_IsNestedPublic;
        VirtualInvokeData get_IsNestedAssembly;
        VirtualInvokeData get_IsExplicitLayout;
        VirtualInvokeData get_IsClass;
        VirtualInvokeData get_IsInterface;
        VirtualInvokeData get_IsValueType;
        VirtualInvokeData get_IsAbstract;
        VirtualInvokeData get_IsSealed;
        VirtualInvokeData get_IsEnum;
        VirtualInvokeData get_IsSerializable;
        VirtualInvokeData get_IsArray;
        VirtualInvokeData get_IsSzArray;
        VirtualInvokeData get_IsGenericType;
        VirtualInvokeData get_IsGenericTypeDefinition;
        VirtualInvokeData get_IsConstructedGenericType;
        VirtualInvokeData get_IsGenericParameter;
        VirtualInvokeData get_GenericParameterPosition;
        VirtualInvokeData get_ContainsGenericParameters;
        VirtualInvokeData GetGenericParameterConstraints;
        VirtualInvokeData get_IsByRef;
        VirtualInvokeData get_IsPointer;
        VirtualInvokeData get_IsPrimitive;
        VirtualInvokeData get_IsCOMObject;
        VirtualInvokeData get_HasElementType;
        VirtualInvokeData get_IsContextful;
        VirtualInvokeData get_IsMarshalByRef;
        VirtualInvokeData IsValueTypeImpl;
        VirtualInvokeData __unknown_25;
        VirtualInvokeData __unknown_26;
        VirtualInvokeData __unknown_27;
        VirtualInvokeData __unknown_28;
        VirtualInvokeData __unknown_29;
        VirtualInvokeData __unknown_30;
        VirtualInvokeData MakeGenericType;
        VirtualInvokeData IsContextfulImpl;
        VirtualInvokeData IsMarshalByRefImpl;
        VirtualInvokeData __unknown_31;
        VirtualInvokeData GetGenericArguments;
        VirtualInvokeData GetGenericTypeDefinition;
        VirtualInvokeData __unknown_32;
        VirtualInvokeData GetEnumNames;
        VirtualInvokeData GetEnumValues;
        VirtualInvokeData GetEnumUnderlyingType;
        VirtualInvokeData IsEnumDefined;
        VirtualInvokeData GetEnumName;
        VirtualInvokeData __unknown_33;
        VirtualInvokeData IsSubclassOf;
        VirtualInvokeData IsInstanceOfType;
        VirtualInvokeData IsAssignableFrom;
        VirtualInvokeData IsEquivalentTo;
        VirtualInvokeData FormatTypeName;
        VirtualInvokeData Equals_1;
        VirtualInvokeData GetType;
        VirtualInvokeData get_IsSZArray;
    };

    struct Type__StaticFields
    {
        void* FilterAttribute;
        void* FilterName;
        void* FilterNameIgnoreCase;
        struct Object* Missing;
        uint16_t Delimiter;
        void* EmptyTypes;
        void* defaultBinder;
    };

    struct Type__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Type__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Type__VTable vtable;
    };
#pragma endregion

#pragma region String
    struct __declspec(align(4)) String__Fields
    {
        int32_t m_stringLength;
        uint16_t m_firstChar;
    };

    struct String
    {
        struct String__Class* klass;
        void* monitor;
        struct String__Fields fields;
    };

    struct String__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData Clone;
        VirtualInvokeData GetTypeCode;
        VirtualInvokeData System_IConvertible_ToBoolean;
        VirtualInvokeData System_IConvertible_ToChar;
        VirtualInvokeData System_IConvertible_ToSByte;
        VirtualInvokeData System_IConvertible_ToByte;
        VirtualInvokeData System_IConvertible_ToInt16;
        VirtualInvokeData System_IConvertible_ToUInt16;
        VirtualInvokeData System_IConvertible_ToInt32;
        VirtualInvokeData System_IConvertible_ToUInt32;
        VirtualInvokeData System_IConvertible_ToInt64;
        VirtualInvokeData System_IConvertible_ToUInt64;
        VirtualInvokeData System_IConvertible_ToSingle;
        VirtualInvokeData System_IConvertible_ToDouble;
        VirtualInvokeData System_IConvertible_ToDecimal;
        VirtualInvokeData System_IConvertible_ToDateTime;
        VirtualInvokeData ToString_1;
        VirtualInvokeData System_IConvertible_ToType;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData CompareTo_1;
        VirtualInvokeData System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
        VirtualInvokeData Equals_1;
    };

    struct String__StaticFields
    {
        struct String* Empty;
    };

    struct String__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct String__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct String__VTable vtable;
    };
#pragma endregion

#pragma region Object_1
    struct __declspec(align(4)) Object_1__Fields
    {
        void* m_CachedPtr;
    };

    struct Object_1
    {
        struct Object_1__Class* klass;
        void* monitor;
        struct Object_1__Fields fields;
    };

    struct Object_1__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Object_1__StaticFields
    {
        int32_t OffsetOfInstanceIDInCPlusPlusObject;
    };

    struct Object_1__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Object_1__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Object_1__VTable vtable;
    };
#pragma endregion

#pragma region Component_1
    struct Component_1__Fields
    {
        struct Object_1__Fields _;
    };

    struct Component_1
    {
        struct Component_1__Class* klass;
        void* monitor;
        struct Component_1__Fields fields;
    };

    struct Component_1__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Component_1__StaticFields
    {
    };

    struct Component_1__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Component_1__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Component_1__VTable vtable;
    };
#pragma endregion

#pragma region Behaviour
    struct Behaviour__Fields
    {
        struct Component_1__Fields _;
    };

    struct Behaviour
    {
        struct Behaviour__Class* klass;
        void* monitor;
        struct Behaviour__Fields fields;
    };

    struct Behaviour__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Behaviour__StaticFields
    {
    };

    struct Behaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Behaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Behaviour__VTable vtable;
    };
#pragma endregion

#pragma region Camera
    struct Camera__Fields
    {
        struct Behaviour__Fields _;
    };

    struct Camera
    {
        struct Camera__Class* klass;
        void* monitor;
        struct Camera__Fields fields;
    };

    struct Camera__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Camera__StaticFields
    {
        void* onPreCull;
        void* onPreRender;
        void* onPostRender;
    };

    struct Camera__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Camera__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Camera__VTable vtable;
    };
#pragma endregion

#pragma region Vector3
    struct Vector3
    {
        float x;
        float y;
        float z;
    };
#pragma endregion

#pragma region Camera__Array
    struct Camera__Array
    {
        struct Camera__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Camera* vector[32];
    };

    struct Camera__Array__VTable
    {
    };

    struct Camera__Array__StaticFields
    {
    };

    struct Camera__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Camera__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Camera__Array__VTable vtable;
    };
#pragma endregion

#pragma region Exception
    struct __declspec(align(4)) Exception__Fields
    {
        struct String* _className;
        struct String* _message;
        void* _data;
        struct Exception* _innerException;
        struct String* _helpURL;
        struct Object* _stackTrace;
        struct String* _stackTraceString;
        struct String* _remoteStackTraceString;
        int32_t _remoteStackIndex;
        struct Object* _dynamicMethods;
        int32_t _HResult;
        struct String* _source;
        void* _safeSerializationManager;
        void* captured_traces;
        void* native_trace_ips;
    };

    struct Exception
    {
        struct Exception__Class* klass;
        void* monitor;
        struct Exception__Fields fields;
    };

    struct Exception__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData GetObjectData;
        VirtualInvokeData get_Message;
        VirtualInvokeData get_Data;
        VirtualInvokeData get_InnerException;
        VirtualInvokeData get_StackTrace;
        VirtualInvokeData get_Source;
        VirtualInvokeData GetObjectData_1;
        VirtualInvokeData GetType;
    };

    struct Exception__StaticFields
    {
        struct Object* s_EDILock;
    };

    struct Exception__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Exception__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Exception__VTable vtable;
    };
#pragma endregion

#pragma region Renderer
    struct Renderer__Fields
    {
        struct Component_1__Fields _;
    };

    struct Renderer
    {
        struct Renderer__Class* klass;
        void* monitor;
        struct Renderer__Fields fields;
    };

    struct Renderer__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Renderer__StaticFields
    {
    };

    struct Renderer__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Renderer__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Renderer__VTable vtable;
    };
#pragma endregion

#pragma region Matrix4x4
    struct Matrix4x4
    {
        float m00;
        float m10;
        float m20;
        float m30;
        float m01;
        float m11;
        float m21;
        float m31;
        float m02;
        float m12;
        float m22;
        float m32;
        float m03;
        float m13;
        float m23;
        float m33;
    };
#pragma endregion

#pragma region Color32
    struct Color32
    {
        union {
            int32_t rgba;
            struct {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t a;
            };
        };
    };
#pragma endregion

#pragma region Color
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    };
#pragma endregion

#pragma region Vector2
    struct Vector2
    {
        float x;
        float y;
    };
#pragma endregion

#pragma region Vector4
    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;
    };
#pragma endregion

#pragma region Transform
    struct Transform__Fields
    {
        struct Component_1__Fields _;
    };

    struct Transform
    {
        struct Transform__Class* klass;
        void* monitor;
        struct Transform__Fields fields;
    };

    struct Transform__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData GetEnumerator;
    };

    struct Transform__StaticFields
    {
    };

    struct Transform__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Transform__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Transform__VTable vtable;
    };
#pragma endregion

#pragma region GameObject
    struct GameObject__Fields
    {
        struct Object_1__Fields _;
    };

    struct GameObject
    {
        struct GameObject__Class* klass;
        void* monitor;
        struct GameObject__Fields fields;
    };

    struct GameObject__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct GameObject__StaticFields
    {
    };

    struct GameObject__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct GameObject__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct GameObject__VTable vtable;
    };
#pragma endregion

#pragma region Object_1__Array
    struct Object_1__Array
    {
        struct Object_1__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Object_1* vector[32];
    };

    struct Object_1__Array__VTable
    {
    };

    struct Object_1__Array__StaticFields
    {
    };

    struct Object_1__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Object_1__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Object_1__Array__VTable vtable;
    };
#pragma endregion

#pragma region SpriteRenderer
    struct SpriteRenderer__Fields
    {
        struct Renderer__Fields _;
    };

    struct SpriteRenderer
    {
        struct SpriteRenderer__Class* klass;
        void* monitor;
        struct SpriteRenderer__Fields fields;
    };

    struct SpriteRenderer__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct SpriteRenderer__StaticFields
    {
    };

    struct SpriteRenderer__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SpriteRenderer__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SpriteRenderer__VTable vtable;
    };
#pragma endregion

#pragma region Color32__Array
    struct Color32__Array
    {
        struct Color32__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Color32 vector[32];
    };
    struct Color32__Array__VTable
    {
    };

    struct Color32__Array__StaticFields
    {
    };

    struct Color32__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Color32__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Color32__Array__VTable vtable;
    };
#pragma endregion

#pragma region Scene
    struct Scene
    {
        int32_t m_Handle;
    };
#pragma endregion

#pragma region Collider2D
    struct Collider2D__Fields
    {
        struct Behaviour__Fields _;
    };

    struct Collider2D
    {
        struct Collider2D__Class* klass;
        void* monitor;
        struct Collider2D__Fields fields;
    };

    struct Collider2D__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Collider2D__StaticFields
    {
    };

    struct Collider2D__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Collider2D__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Collider2D__VTable vtable;
    };
#pragma endregion

#pragma region MessageReader
    struct __declspec(align(4)) MessageReader__Fields
    {
        struct Byte__Array* Buffer;
        uint8_t Tag;
        int32_t Length;
        int32_t Offset;
        struct MessageReader* Parent;
        int32_t _position;
        int32_t readHead;
    };

    struct MessageReader
    {
        struct MessageReader__Class* klass;
        void* monitor;
        struct MessageReader__Fields fields;
    };

    struct MessageReader__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Recycle;
    };

    struct MessageReader__StaticFields
    {
        void* ReaderPool;
    };

    struct MessageReader__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MessageReader__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MessageReader__VTable vtable;
    };
#pragma endregion

#pragma region Byte__Array
    struct Byte__Array
    {
        struct Byte__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        uint8_t vector[32];
    };

    struct Byte__Array__VTable
    {
    };

    struct Byte__Array__StaticFields
    {
    };

    struct Byte__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Byte__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Byte__Array__VTable vtable;
    };
#pragma endregion

#pragma region MessageWriter

#if defined(_CPLUSPLUS_)
    enum class SendOption__Enum : uint8_t
    {
        None = 0x00,
        Reliable = 0x01,
    };

#else
    enum SendOption__Enum
    {
        SendOption__Enum_None = 0x00,
        SendOption__Enum_Reliable = 0x01,
    };

#endif

    struct __declspec(align(4)) MessageWriter__Fields
    {
        struct Byte__Array* Buffer;
        int32_t Length;
        int32_t Position;
#if defined(_CPLUSPLUS_)
        SendOption__Enum _SendOption_k__BackingField;
#else
        uint8_t _SendOption_k__BackingField;
#endif
        void* messageStarts;
    };

    struct MessageWriter
    {
        struct MessageWriter__Class* klass;
        void* monitor;
        struct MessageWriter__Fields fields;
    };

    struct MessageWriter__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Recycle;
    };

    struct MessageWriter__StaticFields
    {
        int32_t BufferSize;
        void* WriterPool;
    };

    struct MessageWriter__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MessageWriter__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MessageWriter__VTable vtable;
    };
#pragma endregion

#pragma region MonoBehaviour
    struct MonoBehaviour__Fields
    {
        struct Behaviour__Fields _;
    };

    struct MonoBehaviour
    {
        struct MonoBehaviour__Class* klass;
        MonitorData* monitor;
        struct MonoBehaviour__Fields fields;
    };

    struct MonoBehaviour__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct MonoBehaviour__StaticFields
    {
    };

    struct MonoBehaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MonoBehaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MonoBehaviour__VTable vtable;
    };
#pragma endregion

#pragma region Extents
    struct Extents
    {
        struct Vector2 min;
        struct Vector2 max;
    };
#pragma endregion

#pragma region TextMeshPro garbage

    struct UIBehaviour__Fields
    {
        struct MonoBehaviour__Fields _;
    };

    struct TextBoxTMP__Fields {
        void* m_CachePtr;
        bool allowAllCharacters;
        struct System_String_o* text;
        struct System_String_o* compoText;
        int32_t characterLimit;
        struct TMPro_TextMeshPro_o* outputText;
        struct UnityEngine_SpriteRenderer_o* Background;
        struct UnityEngine_MeshRenderer_o* Pipe;
        float pipeBlinkTimer;
        bool ClearOnFocus;
        bool ForceUppercase;
        struct UnityEngine_UI_Button_ButtonClickedEvent_o* OnEnter;
        struct UnityEngine_UI_Button_ButtonClickedEvent_o* OnChange;
        struct UnityEngine_UI_Button_ButtonClickedEvent_o* OnFocusLost;
        struct UnityEngine_TouchScreenKeyboard_o* keyboard;
        bool AllowSymbols;
        bool AllowEmail;
        bool IpMode;
        bool AllowPaste;
        bool Hidden;
        struct UnityEngine_Collider2D_array* colliders;
        bool hasFocus;
        struct System_Text_StringBuilder_o* tempTxt;
        struct UnityEngine_SpriteRenderer_o* sendButtonGlyph;
        struct UnityEngine_SpriteRenderer_o* quickChatGlyph;
    };

    struct TextBoxTMP {
        void* klass;
        void* monitor;
        struct TextBoxTMP__Fields fields;
    };

    struct Graphic__Fields
    {
        struct UIBehaviour__Fields _;
        void* m_Material;
        struct Color m_Color;
        bool m_SkipLayoutUpdate;
        bool m_SkipMaterialUpdate;
        bool m_RaycastTarget;
        struct Vector4 m_RaycastPadding;
        void* m_RectTransform;
        void* m_CanvasRenderer;
        void* m_Canvas;
        bool m_VertsDirty;
        bool m_MaterialDirty;
        void* m_OnDirtyLayoutCallback;
        void* m_OnDirtyVertsCallback;
        void* m_OnDirtyMaterialCallback;
        void* m_CachedMesh;
        void* m_CachedUvs;
        void* m_ColorTweenRunner;
        bool _useLegacyMeshGeneration_k__BackingField;
    };

    struct MaskableGraphic__Fields
    {
        struct Graphic__Fields _;
        bool m_ShouldRecalculateStencil;
        void* m_MaskMaterial;
        void* m_ParentMask;
        bool m_Maskable;
        bool m_IsMaskingGraphic;
        bool m_IncludeForMasking;
        void* m_OnCullStateChanged;
        bool m_ShouldRecalculate;
        int32_t m_StencilValue;
        void* m_Corners;
    };

    struct MaterialReference
    {
        int32_t index;
        void* fontAsset;
        void* spriteAsset;
        void* material;
        bool isDefaultMaterial;
        bool isFallbackMaterial;
        void* fallbackMaterial;
        float padding;
        int32_t referenceCount;
    };

    struct TMP_TextProcessingStack_1_MaterialReference_
    {
        void* itemStack;
        int32_t index;
        struct MaterialReference m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct VertexGradient
    {
        struct Color topLeft;
        struct Color topRight;
        struct Color bottomLeft;
        struct Color bottomRight;
    };

    struct TMP_TextProcessingStack_1_System_Single_
    {
        void* itemStack;
        int32_t index;
        float m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_TextProcessingStack_1_FontWeight_
    {
        void* itemStack;
        int32_t index;
        int32_t m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_FontStyleStack
    {
        uint8_t bold;
        uint8_t italic;
        uint8_t underline;
        uint8_t strikethrough;
        uint8_t highlight;
        uint8_t superscript;
        uint8_t subscript;
        uint8_t uppercase;
        uint8_t lowercase;
        uint8_t smallcaps;
    };

    struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_
    {
        void* itemStack;
        int32_t index;
        int32_t m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_LineInfo
    {
        int32_t controlCharacterCount;
        int32_t characterCount;
        int32_t visibleCharacterCount;
        int32_t spaceCount;
        int32_t wordCount;
        int32_t firstCharacterIndex;
        int32_t firstVisibleCharacterIndex;
        int32_t lastCharacterIndex;
        int32_t lastVisibleCharacterIndex;
        float length;
        float lineHeight;
        float ascender;
        float baseline;
        float descender;
        float maxAdvance;
        float width;
        float marginLeft;
        float marginRight;
        int32_t alignment;
        struct Extents lineExtents;
    };

    struct TMP_TextProcessingStack_1_System_Int32_
    {
        void* itemStack;
        int32_t index;
        int32_t m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_TextProcessingStack_1_UnityEngine_Color32_
    {
        void* itemStack;
        int32_t index;
        struct Color32 m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_Offset
    {
        float m_Left;
        float m_Right;
        float m_Top;
        float m_Bottom;
    };

    struct HighlightState
    {
        struct Color32 color;
        struct TMP_Offset padding;
    };

    struct TMP_TextProcessingStack_1_HighlightState_
    {
        void* itemStack;
        int32_t index;
        struct HighlightState m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_TextProcessingStack_1_TMP_ColorGradient_
    {
        void* itemStack;
        int32_t index;
        void* m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct WordWrapState
    {
        int32_t previous_WordBreak;
        int32_t total_CharacterCount;
        int32_t visible_CharacterCount;
        int32_t visible_SpriteCount;
        int32_t visible_LinkCount;
        int32_t firstCharacterIndex;
        int32_t firstVisibleCharacterIndex;
        int32_t lastCharacterIndex;
        int32_t lastVisibleCharIndex;
        int32_t lineNumber;
        float maxCapHeight;
        float maxAscender;
        float maxDescender;
        float startOfLineAscender;
        float maxLineAscender;
        float maxLineDescender;
        float pageAscender;
        int32_t horizontalAlignment;
        float marginLeft;
        float marginRight;
        float xAdvance;
        float preferredWidth;
        float preferredHeight;
        float previousLineScale;
        int32_t wordCount;
        int32_t fontStyle;
        int32_t italicAngle;
        float fontScaleMultiplier;
        float currentFontSize;
        float baselineOffset;
        float lineOffset;
        bool isDrivenLineSpacing;
        float glyphHorizontalAdvanceAdjustment;
        float cSpace;
        float mSpace;
        void* textInfo;
        struct TMP_LineInfo lineInfo;
        struct Color32 vertexColor;
        struct Color32 underlineColor;
        struct Color32 strikethroughColor;
        struct Color32 highlightColor;
        struct TMP_FontStyleStack basicStyleStack;
        struct TMP_TextProcessingStack_1_System_Int32_ italicAngleStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ colorStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ underlineColorStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ strikethroughColorStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ highlightColorStack;
        struct TMP_TextProcessingStack_1_HighlightState_ highlightStateStack;
        struct TMP_TextProcessingStack_1_TMP_ColorGradient_ colorGradientStack;
        struct TMP_TextProcessingStack_1_System_Single_ sizeStack;
        struct TMP_TextProcessingStack_1_System_Single_ indentStack;
        struct TMP_TextProcessingStack_1_FontWeight_ fontWeightStack;
        struct TMP_TextProcessingStack_1_System_Int32_ styleStack;
        struct TMP_TextProcessingStack_1_System_Single_ baselineStack;
        struct TMP_TextProcessingStack_1_System_Int32_ actionStack;
        struct TMP_TextProcessingStack_1_MaterialReference_ materialReferenceStack;
        struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_ lineJustificationStack;
        int32_t spriteAnimationID;
        void* currentFontAsset;
        void* currentSpriteAsset;
        void* currentMaterial;
        int32_t currentMaterialIndex;
        struct Extents meshExtents;
        bool tagNoParsing;
        bool isNonBreakingSpace;
    };

    struct TMP_TextProcessingStack_1_WordWrapState_
    {
        void* itemStack;
        int32_t index;
        struct WordWrapState m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };

    struct TMP_Text_SpecialCharacter
    {
        void* character;
        void* fontAsset;
        void* material;
        int32_t materialIndex;
    };

    struct TMP_Text_TextBackingContainer {
        void* m_Array;
        int32_t m_Count;
    };

#if defined(_CPLUSPLUS_)
    enum class TextAlignmentOptions__Enum : int32_t {
        TopLeft = 0x00000101,
        Top = 0x00000102,
        TopRight = 0x00000104,
        TopJustified = 0x00000108,
        TopFlush = 0x00000110,
        TopGeoAligned = 0x00000120,
        Left = 0x00000201,
        Center = 0x00000202,
        Right = 0x00000204,
        Justified = 0x00000208,
        Flush = 0x00000210,
        CenterGeoAligned = 0x00000220,
        BottomLeft = 0x00000401,
        Bottom = 0x00000402,
        BottomRight = 0x00000404,
        BottomJustified = 0x00000408,
        BottomFlush = 0x00000410,
        BottomGeoAligned = 0x00000420,
        BaselineLeft = 0x00000801,
        Baseline = 0x00000802,
        BaselineRight = 0x00000804,
        BaselineJustified = 0x00000808,
        BaselineFlush = 0x00000810,
        BaselineGeoAligned = 0x00000820,
        MidlineLeft = 0x00001001,
        Midline = 0x00001002,
        MidlineRight = 0x00001004,
        MidlineJustified = 0x00001008,
        MidlineFlush = 0x00001010,
        MidlineGeoAligned = 0x00001020,
        CaplineLeft = 0x00002001,
        Capline = 0x00002002,
        CaplineRight = 0x00002004,
        CaplineJustified = 0x00002008,
        CaplineFlush = 0x00002010,
        CaplineGeoAligned = 0x00002020,
        Converted = 0x0000ffff,
    };

#else
    enum TextAlignmentOptions__Enum {
        TextAlignmentOptions__Enum_TopLeft = 0x00000101,
        TextAlignmentOptions__Enum_Top = 0x00000102,
        TextAlignmentOptions__Enum_TopRight = 0x00000104,
        TextAlignmentOptions__Enum_TopJustified = 0x00000108,
        TextAlignmentOptions__Enum_TopFlush = 0x00000110,
        TextAlignmentOptions__Enum_TopGeoAligned = 0x00000120,
        TextAlignmentOptions__Enum_Left = 0x00000201,
        TextAlignmentOptions__Enum_Center = 0x00000202,
        TextAlignmentOptions__Enum_Right = 0x00000204,
        TextAlignmentOptions__Enum_Justified = 0x00000208,
        TextAlignmentOptions__Enum_Flush = 0x00000210,
        TextAlignmentOptions__Enum_CenterGeoAligned = 0x00000220,
        TextAlignmentOptions__Enum_BottomLeft = 0x00000401,
        TextAlignmentOptions__Enum_Bottom = 0x00000402,
        TextAlignmentOptions__Enum_BottomRight = 0x00000404,
        TextAlignmentOptions__Enum_BottomJustified = 0x00000408,
        TextAlignmentOptions__Enum_BottomFlush = 0x00000410,
        TextAlignmentOptions__Enum_BottomGeoAligned = 0x00000420,
        TextAlignmentOptions__Enum_BaselineLeft = 0x00000801,
        TextAlignmentOptions__Enum_Baseline = 0x00000802,
        TextAlignmentOptions__Enum_BaselineRight = 0x00000804,
        TextAlignmentOptions__Enum_BaselineJustified = 0x00000808,
        TextAlignmentOptions__Enum_BaselineFlush = 0x00000810,
        TextAlignmentOptions__Enum_BaselineGeoAligned = 0x00000820,
        TextAlignmentOptions__Enum_MidlineLeft = 0x00001001,
        TextAlignmentOptions__Enum_Midline = 0x00001002,
        TextAlignmentOptions__Enum_MidlineRight = 0x00001004,
        TextAlignmentOptions__Enum_MidlineJustified = 0x00001008,
        TextAlignmentOptions__Enum_MidlineFlush = 0x00001010,
        TextAlignmentOptions__Enum_MidlineGeoAligned = 0x00001020,
        TextAlignmentOptions__Enum_CaplineLeft = 0x00002001,
        TextAlignmentOptions__Enum_Capline = 0x00002002,
        TextAlignmentOptions__Enum_CaplineRight = 0x00002004,
        TextAlignmentOptions__Enum_CaplineJustified = 0x00002008,
        TextAlignmentOptions__Enum_CaplineFlush = 0x00002010,
        TextAlignmentOptions__Enum_CaplineGeoAligned = 0x00002020,
        TextAlignmentOptions__Enum_Converted = 0x0000ffff,
    };

#endif
#pragma region TMP_Text
    struct TMP_Text__Fields {
        struct MaskableGraphic__Fields _;
        struct String* m_text;
        bool m_IsTextBackingStringDirty;
        void* m_TextPreprocessor;
        bool m_isRightToLeft;
        void* m_fontAsset;
        void* m_currentFontAsset;
        bool m_isSDFShader;
        void* m_sharedMaterial;
        void* m_currentMaterial;
        int32_t m_currentMaterialIndex;
        void* m_fontSharedMaterials;
        void* m_fontMaterial;
        void* m_fontMaterials;
        bool m_isMaterialDirty;
        struct Color32 m_fontColor32;
        struct Color m_fontColor;
        struct Color32 m_underlineColor;
        struct Color32 m_strikethroughColor;
        bool m_enableVertexGradient;
        int32_t m_colorMode;
        struct VertexGradient m_fontColorGradient;
        void* m_fontColorGradientPreset;
        void* m_spriteAsset;
        bool m_tintAllSprites;
        bool m_tintSprite;
        struct Color32 m_spriteColor;
        void* m_StyleSheet;
        void* m_TextStyle;
        int32_t m_TextStyleHashCode;
        bool m_overrideHtmlColors;
        struct Color32 m_faceColor;
        struct Color32 m_outlineColor;
        float m_outlineWidth;
        float m_fontSize;
        float m_currentFontSize;
        float m_fontSizeBase;
        struct TMP_TextProcessingStack_1_System_Single_ m_sizeStack;
        int32_t m_fontWeight;
        int32_t m_FontWeightInternal;
        struct TMP_TextProcessingStack_1_FontWeight_ m_FontWeightStack;
        bool m_enableAutoSizing;
        float m_maxFontSize;
        float m_minFontSize;
        int32_t m_AutoSizeIterationCount;
        int32_t m_AutoSizeMaxIterationCount;
        bool m_IsAutoSizePointSizeSet;
        float m_fontSizeMin;
        float m_fontSizeMax;
        int32_t m_fontStyle;
        int32_t m_FontStyleInternal;
        struct TMP_FontStyleStack m_fontStyleStack;
        bool m_isUsingBold;
        int32_t m_HorizontalAlignment;
        int32_t m_VerticalAlignment;
#if defined(_CPLUSPLUS_)
        TextAlignmentOptions__Enum m_textAlignment;
#else
        int32_t m_textAlignment;
#endif
        int32_t m_lineJustification;
        struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_ m_lineJustificationStack;
        void* m_textContainerLocalCorners;
        float m_characterSpacing;
        float m_cSpacing;
        float m_monoSpacing;
        float m_wordSpacing;
        float m_lineSpacing;
        float m_lineSpacingDelta;
        float m_lineHeight;
        bool m_IsDrivenLineSpacing;
        float m_lineSpacingMax;
        float m_paragraphSpacing;
        float m_charWidthMaxAdj;
        float m_charWidthAdjDelta;
        bool m_enableWordWrapping;
        bool m_isCharacterWrappingEnabled;
        bool m_isNonBreakingSpace;
        bool m_isIgnoringAlignment;
        float m_wordWrappingRatios;
        int32_t m_overflowMode;
        int32_t m_firstOverflowCharacterIndex;
        struct TMP_Text* m_linkedTextComponent;
        struct TMP_Text* parentLinkedComponent;
        bool m_isTextTruncated;
        bool m_enableKerning;
        float m_GlyphHorizontalAdvanceAdjustment;
        bool m_enableExtraPadding;
        bool checkPaddingRequired;
        bool m_isRichText;
        bool m_parseCtrlCharacters;
        bool m_isOverlay;
        bool m_isOrthographic;
        bool m_isCullingEnabled;
        bool m_isMaskingEnabled;
        bool isMaskUpdateRequired;
        bool m_ignoreCulling;
        int32_t m_horizontalMapping;
        int32_t m_verticalMapping;
        float m_uvLineOffset;
        int32_t m_renderMode;
        int32_t m_geometrySortingOrder;
        bool m_IsTextObjectScaleStatic;
        bool m_VertexBufferAutoSizeReduction;
        int32_t m_firstVisibleCharacter;
        int32_t m_maxVisibleCharacters;
        int32_t m_maxVisibleWords;
        int32_t m_maxVisibleLines;
        bool m_useMaxVisibleDescender;
        int32_t m_pageToDisplay;
        bool m_isNewPage;
        struct Vector4 m_margin;
        float m_marginLeft;
        float m_marginRight;
        float m_marginWidth;
        float m_marginHeight;
        float m_width;
        void* m_textInfo;
        bool m_havePropertiesChanged;
        bool m_isUsingLegacyAnimationComponent;
        void* m_transform;
        void* m_rectTransform;
        struct Vector2 m_PreviousRectTransformSize;
        struct Vector2 m_PreviousPivotPosition;
        bool _autoSizeTextContainer_k__BackingField;
        bool m_autoSizeTextContainer;
        void* m_mesh;
        bool m_isVolumetricText;
        void* OnPreRenderText;
        void* m_spriteAnimator;
        float m_flexibleHeight;
        float m_flexibleWidth;
        float m_minWidth;
        float m_minHeight;
        float m_maxWidth;
        float m_maxHeight;
        void* m_LayoutElement;
        float m_preferredWidth;
        float m_renderedWidth;
        bool m_isPreferredWidthDirty;
        float m_preferredHeight;
        float m_renderedHeight;
        bool m_isPreferredHeightDirty;
        bool m_isCalculatingPreferredValues;
        int32_t m_layoutPriority;
        bool m_isLayoutDirty;
        bool m_isAwake;
        bool m_isWaitingOnResourceLoad;
        int32_t m_inputSource;
        float m_fontScaleMultiplier;
        float tag_LineIndent;
        float tag_Indent;
        struct TMP_TextProcessingStack_1_System_Single_ m_indentStack;
        bool tag_NoParsing;
        bool m_isParsingText;
        struct Matrix4x4 m_FXMatrix;
        bool m_isFXMatrixSet;
        void* m_TextProcessingArray;
        int32_t m_InternalTextProcessingArraySize;
        void* m_internalCharacterInfo;
        int32_t m_totalCharacterCount;
        int32_t m_characterCount;
        int32_t m_firstCharacterOfLine;
        int32_t m_firstVisibleCharacterOfLine;
        int32_t m_lastCharacterOfLine;
        int32_t m_lastVisibleCharacterOfLine;
        int32_t m_lineNumber;
        int32_t m_lineVisibleCharacterCount;
        int32_t m_pageNumber;
        float m_PageAscender;
        float m_maxTextAscender;
        float m_maxCapHeight;
        float m_ElementAscender;
        float m_ElementDescender;
        float m_maxLineAscender;
        float m_maxLineDescender;
        float m_startOfLineAscender;
        float m_startOfLineDescender;
        float m_lineOffset;
        struct Extents m_meshExtents;
        struct Color32 m_htmlColor;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_colorStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_underlineColorStack;
        struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_strikethroughColorStack;
        struct TMP_TextProcessingStack_1_HighlightState_ m_HighlightStateStack;
        void* m_colorGradientPreset;
        struct TMP_TextProcessingStack_1_TMP_ColorGradient_ m_colorGradientStack;
        bool m_colorGradientPresetIsTinted;
        float m_tabSpacing;
        float m_spacing;
        void* m_TextStyleStacks;
        int32_t m_TextStyleStackDepth;
        struct TMP_TextProcessingStack_1_System_Int32_ m_ItalicAngleStack;
        int32_t m_ItalicAngle;
        struct TMP_TextProcessingStack_1_System_Int32_ m_actionStack;
        float m_padding;
        float m_baselineOffset;
        struct TMP_TextProcessingStack_1_System_Single_ m_baselineOffsetStack;
        float m_xAdvance;
        int32_t m_textElementType;
        void* m_cached_TextElement;
        struct TMP_Text_SpecialCharacter m_Ellipsis;
        struct TMP_Text_SpecialCharacter m_Underline;
        void* m_defaultSpriteAsset;
        void* m_currentSpriteAsset;
        int32_t m_spriteCount;
        int32_t m_spriteIndex;
        int32_t m_spriteAnimationID;
        bool m_ignoreActiveState;
        struct TMP_Text_TextBackingContainer m_TextBackingArray;
        void* k_Power;
    };

    struct TMP_Text
    {
        struct TMP_Text__Class* klass;
        MonitorData* monitor;
        struct TMP_Text__Fields fields;
    };

    struct TMP_Text__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnEnable;
        VirtualInvokeData Start;
        VirtualInvokeData OnDisable;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData IsActive;
        VirtualInvokeData OnRectTransformDimensionsChange;
        VirtualInvokeData OnBeforeTransformParentChanged;
        VirtualInvokeData OnTransformParentChanged;
        VirtualInvokeData OnDidApplyAnimationProperties;
        VirtualInvokeData OnCanvasGroupChanged;
        VirtualInvokeData OnCanvasHierarchyChanged;
        VirtualInvokeData IsDestroyed;
        VirtualInvokeData Rebuild;
        VirtualInvokeData UnityEngine_UI_ICanvasElement_get_transform;
        VirtualInvokeData LayoutComplete;
        VirtualInvokeData GraphicUpdateComplete;
        VirtualInvokeData IsDestroyed_1;
        VirtualInvokeData get_color;
        VirtualInvokeData set_color;
        VirtualInvokeData get_raycastTarget;
        VirtualInvokeData set_raycastTarget;
        VirtualInvokeData SetAllDirty;
        VirtualInvokeData SetLayoutDirty;
        VirtualInvokeData SetVerticesDirty;
        VirtualInvokeData SetMaterialDirty;
        VirtualInvokeData get_rectTransform;
        VirtualInvokeData get_defaultMaterial;
        VirtualInvokeData get_material;
        VirtualInvokeData set_material;
        VirtualInvokeData get_materialForRendering;
        VirtualInvokeData get_mainTexture;
        VirtualInvokeData OnCullingChanged;
        VirtualInvokeData Rebuild_1;
        VirtualInvokeData LayoutComplete_1;
        VirtualInvokeData GraphicUpdateComplete_1;
        VirtualInvokeData UpdateMaterial;
        VirtualInvokeData UpdateGeometry;
        VirtualInvokeData OnFillVBO;
        VirtualInvokeData OnPopulateMesh;
        VirtualInvokeData OnPopulateMesh_1;
        VirtualInvokeData SetNativeSize;
        VirtualInvokeData Raycast;
        VirtualInvokeData CrossFadeColor;
        VirtualInvokeData CrossFadeColor_1;
        VirtualInvokeData CrossFadeAlpha;
        VirtualInvokeData UnityEngine_UI_IClippable_get_gameObject;
        VirtualInvokeData RecalculateClipping;
        VirtualInvokeData get_rectTransform_1;
        VirtualInvokeData Cull;
        VirtualInvokeData SetClipRect;
        VirtualInvokeData SetClipSoftness;
        VirtualInvokeData RecalculateMasking;
        VirtualInvokeData GetModifiedMaterial;
        VirtualInvokeData GetModifiedMaterial_1;
        VirtualInvokeData Cull_1;
        VirtualInvokeData SetClipRect_1;
        VirtualInvokeData SetClipSoftness_1;
        VirtualInvokeData ParentMaskStateChanged;
        VirtualInvokeData RecalculateClipping_1;
        VirtualInvokeData RecalculateMasking_1;
        VirtualInvokeData get_text;
        VirtualInvokeData set_text;
        VirtualInvokeData get_fontSharedMaterial;
        VirtualInvokeData set_fontSharedMaterial;
        VirtualInvokeData get_fontSharedMaterials;
        VirtualInvokeData set_fontSharedMaterials;
        VirtualInvokeData get_fontMaterials;
        VirtualInvokeData set_fontMaterials;
        VirtualInvokeData get_margin;
        VirtualInvokeData set_margin;
        VirtualInvokeData get_autoSizeTextContainer;
        VirtualInvokeData set_autoSizeTextContainer;
        VirtualInvokeData get_mesh;
        VirtualInvokeData add_OnPreRenderText;
        VirtualInvokeData remove_OnPreRenderText;
        VirtualInvokeData get_flexibleHeight;
        VirtualInvokeData get_flexibleWidth;
        VirtualInvokeData get_minWidth;
        VirtualInvokeData get_minHeight;
        VirtualInvokeData get_preferredWidth;
        VirtualInvokeData get_preferredHeight;
        VirtualInvokeData get_renderedWidth;
        VirtualInvokeData get_renderedHeight;
        VirtualInvokeData get_layoutPriority;
        VirtualInvokeData LoadFontAsset;
        VirtualInvokeData SetSharedMaterial;
        VirtualInvokeData GetMaterial;
        VirtualInvokeData SetFontBaseMaterial;
        VirtualInvokeData GetSharedMaterials;
        VirtualInvokeData SetSharedMaterials;
        VirtualInvokeData GetMaterials;
        VirtualInvokeData CreateMaterialInstance;
        VirtualInvokeData SetFaceColor;
        VirtualInvokeData SetOutlineColor;
        VirtualInvokeData SetOutlineThickness;
        VirtualInvokeData SetShaderDepth;
        VirtualInvokeData SetCulling;
        VirtualInvokeData UpdateCulling;
        VirtualInvokeData GetPaddingForMaterial;
        VirtualInvokeData GetPaddingForMaterial_1;
        VirtualInvokeData GetTextContainerLocalCorners;
        VirtualInvokeData ForceMeshUpdate;
        VirtualInvokeData UpdateGeometry_1;
        VirtualInvokeData UpdateVertexData;
        VirtualInvokeData UpdateVertexData_1;
        VirtualInvokeData SetVertices;
        VirtualInvokeData UpdateMeshPadding;
        VirtualInvokeData InternalCrossFadeColor;
        VirtualInvokeData InternalCrossFadeAlpha;
        VirtualInvokeData SetArraySizes;
        VirtualInvokeData CalculatePreferredValues;
        VirtualInvokeData GetCompoundBounds;
        VirtualInvokeData GetCanvasSpaceClippingRect;
        VirtualInvokeData GetTextInfo;
        VirtualInvokeData ComputeMarginSize;
        VirtualInvokeData SaveGlyphVertexInfo;
        VirtualInvokeData SaveSpriteVertexInfo;
        VirtualInvokeData FillCharacterVertexBuffers;
        VirtualInvokeData FillCharacterVertexBuffers_1;
        VirtualInvokeData FillSpriteVertexBuffers;
        VirtualInvokeData DrawUnderlineMesh;
        VirtualInvokeData DrawTextHighlight;
        VirtualInvokeData SetActiveSubMeshes;
        VirtualInvokeData DestroySubMeshObjects;
        VirtualInvokeData ClearMesh;
        VirtualInvokeData ClearMesh_1;
        VirtualInvokeData GetParsedText;
        VirtualInvokeData InternalUpdate;
    };

    struct TMP_Text__StaticFields {
        // ...
    };

    struct TMP_Text__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct TMP_Text__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct TMP_Text__VTable vtable;
    };
#pragma endregion

#pragma region TextMeshPro
    struct TextMeshPro__Fields
    {
        struct TMP_Text__Fields _;
        bool m_hasFontAssetChanged;
        float m_previousLossyScaleY;
        struct Renderer* m_renderer;
        void* m_meshFilter;
        bool m_isFirstAllocation;
        int32_t m_max_characters;
        int32_t m_max_numberOfLines;
        void* m_subTextObjects;
        int32_t m_maskType;
        struct Matrix4x4 m_EnvMapMatrix;
        void* m_RectTransformCorners;
        bool m_isRegisteredForEvents;
        int32_t _SortingLayer;
        int32_t _SortingLayerID;
        int32_t _SortingOrder;
        void* OnPreRenderText;
        bool m_currentAutoSizeMode;
    };

    struct TextMeshPro
    {
        struct TextMeshPro__Class* klass;
        void* monitor;
        struct TextMeshPro__Fields fields;
    };

    struct TextMeshPro__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnEnable;
        VirtualInvokeData Start;
        VirtualInvokeData OnDisable;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData IsActive;
        VirtualInvokeData OnRectTransformDimensionsChange;
        VirtualInvokeData OnBeforeTransformParentChanged;
        VirtualInvokeData OnTransformParentChanged;
        VirtualInvokeData OnDidApplyAnimationProperties;
        VirtualInvokeData OnCanvasGroupChanged;
        VirtualInvokeData OnCanvasHierarchyChanged;
        VirtualInvokeData IsDestroyed;
        VirtualInvokeData Rebuild;
        VirtualInvokeData UnityEngine_UI_ICanvasElement_get_transform;
        VirtualInvokeData LayoutComplete;
        VirtualInvokeData GraphicUpdateComplete;
        VirtualInvokeData IsDestroyed_1;
        VirtualInvokeData get_color;
        VirtualInvokeData set_color;
        VirtualInvokeData get_raycastTarget;
        VirtualInvokeData set_raycastTarget;
        VirtualInvokeData SetAllDirty;
        VirtualInvokeData SetLayoutDirty;
        VirtualInvokeData SetVerticesDirty;
        VirtualInvokeData SetMaterialDirty;
        VirtualInvokeData get_rectTransform;
        VirtualInvokeData get_defaultMaterial;
        VirtualInvokeData get_material;
        VirtualInvokeData set_material;
        VirtualInvokeData get_materialForRendering;
        VirtualInvokeData get_mainTexture;
        VirtualInvokeData OnCullingChanged;
        VirtualInvokeData Rebuild_1;
        VirtualInvokeData LayoutComplete_1;
        VirtualInvokeData GraphicUpdateComplete_1;
        VirtualInvokeData UpdateMaterial;
        VirtualInvokeData UpdateGeometry;
        VirtualInvokeData OnFillVBO;
        VirtualInvokeData OnPopulateMesh;
        VirtualInvokeData OnPopulateMesh_1;
        VirtualInvokeData SetNativeSize;
        VirtualInvokeData Raycast;
        VirtualInvokeData CrossFadeColor;
        VirtualInvokeData CrossFadeColor_1;
        VirtualInvokeData CrossFadeAlpha;
        VirtualInvokeData UnityEngine_UI_IClippable_get_gameObject;
        VirtualInvokeData RecalculateClipping;
        VirtualInvokeData get_rectTransform_1;
        VirtualInvokeData Cull;
        VirtualInvokeData SetClipRect;
        VirtualInvokeData SetClipSoftness;
        VirtualInvokeData RecalculateMasking;
        VirtualInvokeData GetModifiedMaterial;
        VirtualInvokeData GetModifiedMaterial_1;
        VirtualInvokeData Cull_1;
        VirtualInvokeData SetClipRect_1;
        VirtualInvokeData SetClipSoftness_1;
        VirtualInvokeData ParentMaskStateChanged;
        VirtualInvokeData RecalculateClipping_1;
        VirtualInvokeData RecalculateMasking_1;
        VirtualInvokeData get_text;
        VirtualInvokeData set_text;
        VirtualInvokeData get_fontSharedMaterial;
        VirtualInvokeData set_fontSharedMaterial;
        VirtualInvokeData get_fontSharedMaterials;
        VirtualInvokeData set_fontSharedMaterials;
        VirtualInvokeData get_fontMaterials;
        VirtualInvokeData set_fontMaterials;
        VirtualInvokeData get_margin;
        VirtualInvokeData set_margin;
        VirtualInvokeData get_autoSizeTextContainer;
        VirtualInvokeData set_autoSizeTextContainer;
        VirtualInvokeData get_mesh;
        VirtualInvokeData add_OnPreRenderText;
        VirtualInvokeData remove_OnPreRenderText;
        VirtualInvokeData get_flexibleHeight;
        VirtualInvokeData get_flexibleWidth;
        VirtualInvokeData get_minWidth;
        VirtualInvokeData get_minHeight;
        VirtualInvokeData get_preferredWidth;
        VirtualInvokeData get_preferredHeight;
        VirtualInvokeData get_renderedWidth;
        VirtualInvokeData get_renderedHeight;
        VirtualInvokeData get_layoutPriority;
        VirtualInvokeData LoadFontAsset;
        VirtualInvokeData SetSharedMaterial;
        VirtualInvokeData GetMaterial;
        VirtualInvokeData SetFontBaseMaterial;
        VirtualInvokeData GetSharedMaterials;
        VirtualInvokeData SetSharedMaterials;
        VirtualInvokeData GetMaterials;
        VirtualInvokeData CreateMaterialInstance;
        VirtualInvokeData SetFaceColor;
        VirtualInvokeData SetOutlineColor;
        VirtualInvokeData SetOutlineThickness;
        VirtualInvokeData SetShaderDepth;
        VirtualInvokeData SetCulling;
        VirtualInvokeData UpdateCulling;
        VirtualInvokeData GetPaddingForMaterial;
        VirtualInvokeData GetPaddingForMaterial_1;
        VirtualInvokeData GetTextContainerLocalCorners;
        VirtualInvokeData ForceMeshUpdate;
        VirtualInvokeData UpdateGeometry_1;
        VirtualInvokeData UpdateVertexData;
        VirtualInvokeData UpdateVertexData_1;
        VirtualInvokeData SetVertices;
        VirtualInvokeData UpdateMeshPadding;
        VirtualInvokeData InternalCrossFadeColor;
        VirtualInvokeData InternalCrossFadeAlpha;
        VirtualInvokeData SetArraySizes;
        VirtualInvokeData CalculatePreferredValues;
        VirtualInvokeData GetCompoundBounds;
        VirtualInvokeData GetCanvasSpaceClippingRect;
        VirtualInvokeData GetTextInfo;
        VirtualInvokeData ComputeMarginSize;
        VirtualInvokeData SaveGlyphVertexInfo;
        VirtualInvokeData SaveSpriteVertexInfo;
        VirtualInvokeData FillCharacterVertexBuffers;
        VirtualInvokeData FillCharacterVertexBuffers_1;
        VirtualInvokeData FillSpriteVertexBuffers;
        VirtualInvokeData DrawUnderlineMesh;
        VirtualInvokeData DrawTextHighlight;
        VirtualInvokeData SetActiveSubMeshes;
        VirtualInvokeData DestroySubMeshObjects;
        VirtualInvokeData ClearMesh;
        VirtualInvokeData ClearMesh_1;
        VirtualInvokeData GetParsedText;
        VirtualInvokeData InternalUpdate;
        VirtualInvokeData CalculateLayoutInputHorizontal;
        VirtualInvokeData CalculateLayoutInputVertical;
        VirtualInvokeData get_minWidth_1;
        VirtualInvokeData get_preferredWidth_1;
        VirtualInvokeData get_flexibleWidth_1;
        VirtualInvokeData get_minHeight_1;
        VirtualInvokeData get_preferredHeight_1;
        VirtualInvokeData get_flexibleHeight_1;
        VirtualInvokeData get_layoutPriority_1;
        VirtualInvokeData GenerateTextMesh;
    };

    struct TextMeshPro__StaticFields
    {
    };

    struct TextMeshPro__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct TextMeshPro__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct TextMeshPro__VTable vtable;
    };
#pragma endregion
#pragma endregion

#pragma region PlayerOutfitType__Enum
#if defined(_CPLUSPLUS_)
    enum class PlayerOutfitType__Enum : int32_t
    {
        Default = 0x00000000,
        Shapeshifted = 0x00000001,
    };

#else
    enum PlayerOutfitType__Enum
    {
        PlayerOutfitType__Enum_Default = 0x00000000,
        PlayerOutfitType__Enum_Shapeshifted = 0x00000001,
    };

#endif
#pragma endregion

#pragma region AccountTab
    struct AccountTab__Fields
    {
        struct MonoBehaviour__Fields _;
        struct TextMeshPro* userName;
        struct TextMeshPro* friendCode;
        struct TextMeshPro* friendCodeTitle;
        void* playerImage; // struct PoolablePlayer, not actual img
        struct SpriteRenderer* FriendCodeHiddenIcon;
        struct GameObject* offlineMode;
        struct GameObject* guestMode;
        struct FullAccount* loggedInMode;
        struct GameObject* waitingForGuardian;
        struct TextMeshPro* guardianEmailText;
        void* editNameScreen;
        struct GameObject* idCard;
        struct SpriteRenderer* actualTabSprite;
        struct GameObject* resendEmailButton;
        void* LinkExistingAccountPopup;
        struct TextMeshPro* levelText;
        void* xpProgressBar;
        struct GameObject* signIntoAccountButton;
        struct GameObject* askForGuardianEmailButton;
        struct TextMeshPro* veryBadErrorText;
        struct Collider2D* clickToCloseCollider;
        struct TextMeshPro* accountIDDisplayText;
        struct GameObject* showAccountIDButton;
        struct SpriteRenderer* SpaceBean;
        struct SpriteRenderer* SpaceHorse;
        bool showAccountID;
        struct String* friendCodeHiddenText;
        void* BackButton;
        void* PotentialDefaultSelections;
        void* selectableObjects;
    };

    struct AccountTab
    {
        struct AccountTab__Class* klass;
        void* monitor;
        struct AccountTab__Fields fields;
    };

    struct AccountTab__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct AccountTab__StaticFields
    {
    };

    struct AccountTab__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct AccountTab__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct AccountTab__VTable vtable;
    };
#pragma endregion

#pragma region EOSManager
    struct EOSManager
    {
        struct EOSManager__Class* klass;
        void* monitor;
        //struct EOSManager__Fields fields;
    };

    struct EOSManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct EOSManager__StaticFields
    {
    };

    struct EOSManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct EOSManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct EOSManager__VTable vtable;
    };
#pragma endregion

#pragma region FullAccount
    struct FullAccount__Fields {
        struct MonoBehaviour__Fields _;
        struct GameObject* randomizeNameButton;
        struct GameObject* editNameButton;
        struct GameObject* manageAccount;
    };

    struct FullAccount
    {
        struct FullAccount__Class* klass;
        void* monitor;
        struct FullAccount__Fields fields;
    };

    struct FullAccount__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct FullAccount__StaticFields
    {
    };

    struct FullAccount__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct FullAccount__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct FullAccount__VTable vtable;
    };
#pragma endregion

#pragma region InnerNetObject

#if defined(_CPLUSPLUS_)
    enum class SpawnFlags__Enum : uint8_t
    {
        None = 0x00,
        IsClientCharacter = 0x01,
    };

#else
    enum SpawnFlags__Enum
    {
        SpawnFlags__Enum_None = 0x00,
        SpawnFlags__Enum_IsClientCharacter = 0x01,
    };

#endif

    struct InnerNetObject__Fields
    {
        struct MonoBehaviour__Fields _;
        uint32_t SpawnId;
        uint32_t NetId;
        uint32_t DirtyBits;
#if defined(_CPLUSPLUS_)
        SpawnFlags__Enum SpawnFlags;
#else
        uint8_t SpawnFlags;
#endif
#if defined(_CPLUSPLUS_)
        SendOption__Enum sendMode;
#else
        uint8_t sendMode;
#endif
        int32_t OwnerId;
        bool DespawnOnDestroy;
    };

    struct InnerNetObject
    {
        struct InnerNetObject__Class* klass;
        void* monitor;
        struct InnerNetObject__Fields fields;
    };

    struct InnerNetObject__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData __unknown;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
    };

    struct InnerNetObject__StaticFields
    {
    };

    struct InnerNetObject__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct InnerNetObject__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct InnerNetObject__VTable vtable;
    };
#pragma endregion

#pragma region PlainDoor__Array
    struct PlainDoor__Array
    {
        struct PlainDoor__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlainDoor* vector[32];
    };

    struct PlainDoor__Array__VTable
    {
    };

    struct PlainDoor__Array__StaticFields
    {
    };

    struct PlainDoor__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlainDoor__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlainDoor__Array__VTable vtable;
    };
#pragma endregion

#pragma region PlayerVoteArea
    struct PlayerVoteArea__Fields {
        struct MonoBehaviour__Fields _;
        struct MeetingHud* _Parent_k__BackingField;
        uint8_t TargetPlayerId;
        struct GameObject* Buttons;
        void* ConfirmButton;
        void* CancelButton;
        void* PlayerButton;
        struct SpriteRenderer* Background;
        struct SpriteRenderer* MaskArea;
        struct SpriteRenderer* Flag;
        struct SpriteRenderer* Megaphone;
        struct SpriteRenderer* Overlay;
        struct SpriteRenderer* XMark;
        struct SpriteRenderer* GAIcon;
        struct SpriteRenderer* ThumbsDown;
        struct SpriteRenderer* HighlightedFX;
        struct TextMeshPro* NameText;
        struct TextMeshPro* LevelNumberText;
        struct TextMeshPro* ColorBlindName;
        bool AnimateButtonsFromLeft;
        bool AmDead;
        bool DidReport;
        uint8_t VotedFor;
        bool voteComplete;
        bool resultsShowing;
        void* PlayerIcon;
    };

    struct PlayerVoteArea {
        struct PlayerVoteArea__Class* klass;
        MonitorData* monitor;
        struct PlayerVoteArea__Fields fields;
    };

    struct PlayerVoteArea__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct PlayerVoteArea__StaticFields
    {
    };

    struct PlayerVoteArea__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerVoteArea__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerVoteArea__VTable vtable;
    };
#pragma endregion

#pragma region PlayerVoteArea__Array
    struct PlayerVoteArea__Array
    {
        struct PlayerVoteArea__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlayerVoteArea* vector[32];
    };

    struct PlayerVoteArea__Array__VTable
    {
    };

    struct PlayerVoteArea__Array__StaticFields
    {
    };

    struct PlayerVoteArea__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerVoteArea__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerVoteArea__Array__VTable vtable;
    };
#pragma endregion

#pragma region SystemTypes__Enum
#if defined(_CPLUSPLUS_)
    enum class SystemTypes__Enum : uint8_t {
        Hallway = 0x00,
        Storage = 0x01,
        Cafeteria = 0x02,
        Reactor = 0x03,
        UpperEngine = 0x04,
        Nav = 0x05,
        Admin = 0x06,
        Electrical = 0x07,
        LifeSupp = 0x08,
        Shields = 0x09,
        MedBay = 0x0a,
        Security = 0x0b,
        Weapons = 0x0c,
        LowerEngine = 0x0d,
        Comms = 0x0e,
        ShipTasks = 0x0f,
        Doors = 0x10,
        Sabotage = 0x11,
        Decontamination = 0x12,
        Launchpad = 0x13,
        LockerRoom = 0x14,
        Laboratory = 0x15,
        Balcony = 0x16,
        Office = 0x17,
        Greenhouse = 0x18,
        Dropship = 0x19,
        Decontamination2 = 0x1a,
        Outside = 0x1b,
        Specimens = 0x1c,
        BoilerRoom = 0x1d,
        VaultRoom = 0x1e,
        Cockpit = 0x1f,
        Armory = 0x20,
        Kitchen = 0x21,
        ViewingDeck = 0x22,
        HallOfPortraits = 0x23,
        CargoBay = 0x24,
        Ventilation = 0x25,
        Showers = 0x26,
        Engine = 0x27,
        Brig = 0x28,
        MeetingRoom = 0x29,
        Records = 0x2a,
        Lounge = 0x2b,
        GapRoom = 0x2c,
        MainHall = 0x2d,
        Medical = 0x2e,
        Decontamination3 = 0x2f,
    };

#else
    enum SystemTypes__Enum {
        SystemTypes__Enum_Hallway = 0x00,
        SystemTypes__Enum_Storage = 0x01,
        SystemTypes__Enum_Cafeteria = 0x02,
        SystemTypes__Enum_Reactor = 0x03,
        SystemTypes__Enum_UpperEngine = 0x04,
        SystemTypes__Enum_Nav = 0x05,
        SystemTypes__Enum_Admin = 0x06,
        SystemTypes__Enum_Electrical = 0x07,
        SystemTypes__Enum_LifeSupp = 0x08,
        SystemTypes__Enum_Shields = 0x09,
        SystemTypes__Enum_MedBay = 0x0a,
        SystemTypes__Enum_Security = 0x0b,
        SystemTypes__Enum_Weapons = 0x0c,
        SystemTypes__Enum_LowerEngine = 0x0d,
        SystemTypes__Enum_Comms = 0x0e,
        SystemTypes__Enum_ShipTasks = 0x0f,
        SystemTypes__Enum_Doors = 0x10,
        SystemTypes__Enum_Sabotage = 0x11,
        SystemTypes__Enum_Decontamination = 0x12,
        SystemTypes__Enum_Launchpad = 0x13,
        SystemTypes__Enum_LockerRoom = 0x14,
        SystemTypes__Enum_Laboratory = 0x15,
        SystemTypes__Enum_Balcony = 0x16,
        SystemTypes__Enum_Office = 0x17,
        SystemTypes__Enum_Greenhouse = 0x18,
        SystemTypes__Enum_Dropship = 0x19,
        SystemTypes__Enum_Decontamination2 = 0x1a,
        SystemTypes__Enum_Outside = 0x1b,
        SystemTypes__Enum_Specimens = 0x1c,
        SystemTypes__Enum_BoilerRoom = 0x1d,
        SystemTypes__Enum_VaultRoom = 0x1e,
        SystemTypes__Enum_Cockpit = 0x1f,
        SystemTypes__Enum_Armory = 0x20,
        SystemTypes__Enum_Kitchen = 0x21,
        SystemTypes__Enum_ViewingDeck = 0x22,
        SystemTypes__Enum_HallOfPortraits = 0x23,
        SystemTypes__Enum_CargoBay = 0x24,
        SystemTypes__Enum_Ventilation = 0x25,
        SystemTypes__Enum_Showers = 0x26,
        SystemTypes__Enum_Engine = 0x27,
        SystemTypes__Enum_Brig = 0x28,
        SystemTypes__Enum_MeetingRoom = 0x29,
        SystemTypes__Enum_Records = 0x2a,
        SystemTypes__Enum_Lounge = 0x2b,
        SystemTypes__Enum_GapRoom = 0x2c,
        SystemTypes__Enum_MainHall = 0x2d,
        SystemTypes__Enum_Medical = 0x2e,
        SystemTypes__Enum_Decontamination3 = 0x2f,
    };

#endif
#pragma endregion

#pragma region PlainShipRoom
    struct PlainShipRoom__Fields
    {
        struct MonoBehaviour__Fields _;
#if defined(_CPLUSPLUS_)
        SystemTypes__Enum RoomId;
#else
        uint8_t RoomId;
#endif
        void* survCamera;
        struct Collider2D* roomArea;
    };

    struct PlainShipRoom
    {
        struct PlainShipRoom__Class* klass;
        MonitorData* monitor;
        struct PlainShipRoom__Fields fields;
    };
    struct PlainShipRoom__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct PlainShipRoom__StaticFields
    {
    };

    struct PlainShipRoom__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlainShipRoom__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlainShipRoom__VTable vtable;
    };
#pragma endregion

#pragma region PlainShipRoom__Array
    struct PlainShipRoom__Array
    {
        struct PlainShipRoom__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlainShipRoom* vector[32];
    };
    struct PlainShipRoom__Array__VTable
    {
    };

    struct PlainShipRoom__Array__StaticFields
    {
    };

    struct PlainShipRoom__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlainShipRoom__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlainShipRoom__Array__VTable vtable;
    };
#pragma endregion

#pragma region ShipStatus

#if defined(_CPLUSPLUS_)
    enum class ShipStatus_MapType__Enum : int32_t
    {
        Ship = 0x00000000,
        Hq = 0x00000001,
        Pb = 0x00000002,
    };

#else
    enum ShipStatus_MapType__Enum
    {
        ShipStatus_MapType__Enum_Ship = 0x00000000,
        ShipStatus_MapType__Enum_Hq = 0x00000001,
        ShipStatus_MapType__Enum_Pb = 0x00000002,
    };

#endif

    struct ShipStatus__Fields {
        struct InnerNetObject__Fields _;
        struct Color CameraColor;
        float MaxLightRadius;
        float MinLightRadius;
        float MapScale;
        void* MapPrefab;
        void* ExileCutscenePrefab;
        void* EmergencyOverlay;
        void* ReportOverlay;
        void* MeetingBackground;
        void* EmergencyButton;
        struct Vector2 InitialSpawnCenter;
        struct Vector2 MeetingSpawnCenter;
        struct Vector2 MeetingSpawnCenter2;
        float SpawnRadius;
        void* CommonTasks;
        void* LongTasks;
        void* NormalTasks;
        struct PlayerTask__Array* SpecialTasks;
        void* DummyLocations;
        void* AllCameras;
        struct PlainDoor__Array* AllDoors;
        void* AllConsoles;
        struct Dictionary_2_SystemTypes_ISystemType_* Systems;
        void* SystemNames;
        void* _AllStepWatchers_k__BackingField;
        struct PlainShipRoom__Array* _AllRooms_k__BackingField;
        void* _FastRooms_k__BackingField;
        void* _AllVents_k__BackingField;
        void* SabotageSound;
        void* WeaponFires;
        void* WeaponsImage;
        void* VentMoveSounds;
        void* VentEnterSound;
        void* HatchActive;
        void* Hatch;
        void* HatchParticles;
        void* ShieldsActive;
        void* ShieldsImages;
        struct SpriteRenderer* ShieldBorder;
        void* ShieldBorderOn;
        void* MedScanner;
        int32_t WeaponFireIdx;
        float Timer;
        float EmergencyCooldown;
#if defined(_CPLUSPLUS_)
        ShipStatus_MapType__Enum Type;
#else
        int32_t Type;
#endif
        float _HideCountdown_k__BackingField;
        void* _CosmeticsCache_k__BackingField;
        void* logger;
        int32_t numScans;
    };

    struct ShipStatus {
        struct ShipStatus__Class* klass;
        MonitorData* monitor;
        struct ShipStatus__Fields fields;
    };

    struct ShipStatus__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData OnEnable;
        VirtualInvokeData RepairGameOverSystems;
        VirtualInvokeData Start;
        VirtualInvokeData SpawnPlayer;
        VirtualInvokeData OnMeetingCalled;
        VirtualInvokeData PrespawnStep;
        VirtualInvokeData CalculateLightRadius;
    };

    struct ShipStatus__StaticFields
    {
        struct ShipStatus* Instance;
    };

    struct ShipStatus__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ShipStatus__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ShipStatus__VTable vtable;
    };
#pragma endregion

#pragma region StringNames__Enum

#if defined(_CPLUSPLUS_)
    enum class StringNames__Enum : int32_t {
        ExitButton = 0x00000000,
        BackButton = 0x00000001,
        AvailableGamesLabel = 0x00000002,
        CreateGameButton = 0x00000003,
        FindGameButton = 0x00000004,
        EnterCode = 0x00000005,
        GhostIgnoreTasks = 0x00000006,
        GhostDoTasks = 0x00000007,
        GhostImpostor = 0x00000008,
        ImpostorTask = 0x00000009,
        FakeTasks = 0x0000000a,
        TaskComplete = 0x0000000b,
        ExileTextSP = 0x0000000c,
        ExileTextSN = 0x0000000d,
        ExileTextPP = 0x0000000e,
        ExileTextPN = 0x0000000f,
        NoExileSkip = 0x00000010,
        NoExileTie = 0x00000011,
        ImpostorsRemainS = 0x00000012,
        ImpostorsRemainP = 0x00000013,
        Hallway = 0x00000014,
        Storage = 0x00000015,
        Cafeteria = 0x00000016,
        Reactor = 0x00000017,
        UpperEngine = 0x00000018,
        Nav = 0x00000019,
        Admin = 0x0000001a,
        Electrical = 0x0000001b,
        LifeSupp = 0x0000001c,
        Shields = 0x0000001d,
        MedBay = 0x0000001e,
        Security = 0x0000001f,
        Weapons = 0x00000020,
        LowerEngine = 0x00000021,
        Comms = 0x00000022,
        Decontamination = 0x00000023,
        Launchpad = 0x00000024,
        LockerRoom = 0x00000025,
        Laboratory = 0x00000026,
        Balcony = 0x00000027,
        Office = 0x00000028,
        Greenhouse = 0x00000029,
        DivertPowerTo = 0x0000002a,
        AcceptDivertedPower = 0x0000002b,
        SubmitScan = 0x0000002c,
        PrimeShields = 0x0000002d,
        FuelEngines = 0x0000002e,
        ChartCourse = 0x0000002f,
        StartReactor = 0x00000030,
        SwipeCard = 0x00000031,
        ClearAsteroids = 0x00000032,
        UploadData = 0x00000033,
        DownloadData = 0x00000034,
        InspectSample = 0x00000035,
        EmptyChute = 0x00000036,
        EmptyGarbage = 0x00000037,
        AlignEngineOutput = 0x00000038,
        FixWiring = 0x00000039,
        CalibrateDistributor = 0x0000003a,
        UnlockManifolds = 0x0000003b,
        ResetReactor = 0x0000003c,
        FixLights = 0x0000003d,
        FixComms = 0x0000003e,
        RestoreOxy = 0x0000003f,
        CleanO2Filter = 0x00000040,
        StabilizeSteering = 0x00000041,
        AssembleArtifact = 0x00000042,
        SortSamples = 0x00000043,
        MeasureWeather = 0x00000044,
        EnterIdCode = 0x00000045,
        HowToPlayText1 = 0x00000046,
        HowToPlayText2 = 0x00000047,
        HowToPlayText5 = 0x00000048,
        HowToPlayText6 = 0x00000049,
        HowToPlayText7 = 0x0000004a,
        HowToPlayText81 = 0x0000004b,
        HowToPlayText82 = 0x0000004c,
        NumImpostorsS = 0x0000004d,
        NumImpostorsP = 0x0000004e,
        Crewmate = 0x0000004f,
        Impostor = 0x00000050,
        Victory = 0x00000051,
        Defeat = 0x00000052,
        CrewmatesDisconnected = 0x00000053,
        ImpostorDisconnected = 0x00000054,
        HowToPlayText41 = 0x00000055,
        HowToPlayText42 = 0x00000056,
        HowToPlayText43 = 0x00000057,
        HowToPlayText44 = 0x00000058,
        HowToPlayTextMap = 0x00000059,
        HowToPlayTextCrew1 = 0x0000005a,
        HowToPlayTextCrew2 = 0x0000005b,
        HowToPlayTextCrew3 = 0x0000005c,
        HowToPlayTextCrew4 = 0x0000005d,
        HowToPlayTextCrew5 = 0x0000005e,
        HowToPlayTextCrew6 = 0x0000005f,
        HowToPlayTextImp1 = 0x00000060,
        HowToPlayTextImp2 = 0x00000061,
        HowToPlayTextImp3 = 0x00000062,
        HowToPlayTextImp4 = 0x00000063,
        HowToPlayTextImp5 = 0x00000064,
        HowToPlayTextImp6 = 0x00000065,
        HowToPlayTextImp7 = 0x00000066,
        SettingsGeneral = 0x00000067,
        SettingsControls = 0x00000068,
        SettingsSound = 0x00000069,
        SettingsGraphics = 0x0000006a,
        SettingsData = 0x0000006b,
        SettingsCensorChat = 0x0000006c,
        SettingsMusic = 0x0000006d,
        SettingsSFX = 0x0000006e,
        SettingsOn = 0x0000006f,
        SettingsOff = 0x00000070,
        SettingsSendTelemetry = 0x00000071,
        SettingsControlMode = 0x00000072,
        SettingsTouchMode = 0x00000073,
        SettingsJoystickMode = 0x00000074,
        SettingsKeyboardMode = 0x00000075,
        SettingsFullscreen = 0x00000076,
        SettingsResolution = 0x00000077,
        SettingsApply = 0x00000078,
        SettingsPersonalizeAds = 0x00000079,
        SettingsLanguage = 0x0000007a,
        SettingsJoystickSize = 0x0000007b,
        SettingsMouseMode = 0x0000007c,
        PlayerColor = 0x0000007d,
        PlayerHat = 0x0000007e,
        PlayerSkin = 0x0000007f,
        PlayerPet = 0x00000080,
        GameSettings = 0x00000081,
        GameRecommendedSettings = 0x00000082,
        GameCustomSettings = 0x00000083,
        GameMapName = 0x00000084,
        GameNumImpostors = 0x00000085,
        GameNumMeetings = 0x00000086,
        GameDiscussTime = 0x00000087,
        GameVotingTime = 0x00000088,
        GamePlayerSpeed = 0x00000089,
        GameCrewLight = 0x0000008a,
        GameImpostorLight = 0x0000008b,
        GameKillCooldown = 0x0000008c,
        GameKillDistance = 0x0000008d,
        GameCommonTasks = 0x0000008e,
        GameLongTasks = 0x0000008f,
        GameShortTasks = 0x00000090,
        MatchMapName = 0x00000091,
        MatchLanguage = 0x00000092,
        MatchImpostors = 0x00000093,
        MatchMaxPlayers = 0x00000094,
        Cancel = 0x00000095,
        Confirm = 0x00000096,
        Limit = 0x00000097,
        RoomCode = 0x00000098,
        LeaveGame = 0x00000099,
        ReturnToGame = 0x0000009a,
        LocalHelp = 0x0000009b,
        OnlineHelp = 0x0000009c,
        SettingsVSync = 0x0000009d,
        EmergencyCount = 0x0000009e,
        EmergencyNotReady = 0x0000009f,
        EmergencyDuringCrisis = 0x000000a0,
        EmergencyRequested = 0x000000a1,
        GameEmergencyCooldown = 0x000000a2,
        BuyBeverage = 0x000000a3,
        WeatherEta = 0x000000a4,
        WeatherComplete = 0x000000a5,
        ProcessData = 0x000000a6,
        RunDiagnostics = 0x000000a7,
        WaterPlants = 0x000000a8,
        PickAnomaly = 0x000000a9,
        WaterPlantsGetCan = 0x000000aa,
        AuthOfficeOkay = 0x000000ab,
        AuthCommsOkay = 0x000000ac,
        AuthOfficeActive = 0x000000ad,
        AuthCommsActive = 0x000000ae,
        AuthOfficeNotActive = 0x000000af,
        AuthCommsNotActive = 0x000000b0,
        SecLogEntry = 0x000000b1,
        EnterName = 0x000000b2,
        SwipeCardPleaseSwipe = 0x000000b3,
        SwipeCardBadRead = 0x000000b4,
        SwipeCardTooFast = 0x000000b5,
        SwipeCardTooSlow = 0x000000b6,
        SwipeCardAccepted = 0x000000b7,
        ReactorHoldToStop = 0x000000b8,
        ReactorWaiting = 0x000000b9,
        ReactorNominal = 0x000000ba,
        MeetingWhoIsTitle = 0x000000bb,
        MeetingVotingBegins = 0x000000bc,
        MeetingVotingEnds = 0x000000bd,
        MeetingVotingResults = 0x000000be,
        MeetingProceeds = 0x000000bf,
        MeetingHasVoted = 0x000000c0,
        DataPolicyTitle = 0x000000c1,
        DataPolicyText = 0x000000c2,
        DataPolicyWhat = 0x000000c3,
        AdPolicyTitle = 0x000000c4,
        AdPolicyText = 0x000000c5,
        Accept = 0x000000c6,
        RemoveAds = 0x000000c7,
        SwipeCardPleaseInsert = 0x000000c8,
        LogNorth = 0x000000c9,
        LogSouthEast = 0x000000ca,
        LogSouthWest = 0x000000cb,
        SettingShort = 0x000000cc,
        SettingMedium = 0x000000cd,
        SettingLong = 0x000000ce,
        SamplesPress = 0x000000cf,
        SamplesAdding = 0x000000d0,
        SamplesSelect = 0x000000d1,
        SamplesThanks = 0x000000d2,
        SamplesComplete = 0x000000d3,
        AstDestroyed = 0x000000d4,
        TaskTestTitle = 0x000000d5,
        BeginDiagnostics = 0x000000d6,
        UserLeftGame = 0x000000d7,
        GameStarting = 0x000000d8,
        Tasks = 0x000000d9,
        StatsTitle = 0x000000da,
        StatsBodiesReported = 0x000000db,
        StatsEmergenciesCalled = 0x000000dc,
        StatsTasksCompleted = 0x000000dd,
        StatsAllTasksCompleted = 0x000000de,
        StatsSabotagesFixed = 0x000000df,
        StatsImpostorKills = 0x000000e0,
        StatsTimesMurdered = 0x000000e1,
        StatsTimesEjected = 0x000000e2,
        StatsCrewmateStreak = 0x000000e3,
        StatsGamesImpostor = 0x000000e4,
        StatsGamesCrewmate = 0x000000e5,
        StatsGamesStarted = 0x000000e6,
        StatsGamesFinished = 0x000000e7,
        StatsImpostorVoteWins = 0x000000e8,
        StatsImpostorKillsWins = 0x000000e9,
        StatsImpostorSabotageWins = 0x000000ea,
        StatsCrewmateVoteWins = 0x000000eb,
        StatsCrewmateTaskWins = 0x000000ec,
        MedscanRequested = 0x000000ed,
        MedscanWaitingFor = 0x000000ee,
        MedscanCompleted = 0x000000ef,
        MedscanCompleteIn = 0x000000f0,
        MonitorOxygen = 0x000000f1,
        StoreArtifacts = 0x000000f2,
        FillCanisters = 0x000000f3,
        FixWeatherNode = 0x000000f4,
        InsertKeys = 0x000000f5,
        ResetSeismic = 0x000000f6,
        SeismicHoldToStop = 0x000000f7,
        SeismicNominal = 0x000000f8,
        ScanBoardingPass = 0x000000f9,
        OpenWaterways = 0x000000fa,
        ReplaceWaterJug = 0x000000fb,
        RepairDrill = 0x000000fc,
        AlignTelescope = 0x000000fd,
        RecordTemperature = 0x000000fe,
        RebootWifi = 0x000000ff,
        WifiRebootRequired = 0x00000100,
        WifiPleasePowerOn = 0x00000101,
        WifiPleaseWait = 0x00000102,
        WifiPleaseReturnIn = 0x00000103,
        WifiRebootComplete = 0x00000104,
        Outside = 0x00000105,
        GameSecondsAbbrev = 0x00000106,
        Engines = 0x00000107,
        Dropship = 0x00000108,
        Decontamination2 = 0x00000109,
        Specimens = 0x0000010a,
        BoilerRoom = 0x0000010b,
        GameOverImpostorDead = 0x0000010c,
        GameOverImpostorKills = 0x0000010d,
        GameOverTaskWin = 0x0000010e,
        GameOverSabotage = 0x0000010f,
        GameConfirmImpostor = 0x00000110,
        GameVisualTasks = 0x00000111,
        ExileTextNonConfirm = 0x00000112,
        GameAnonymousVotes = 0x00000113,
        GameTaskBarMode = 0x00000114,
        SettingNormalTaskMode = 0x00000115,
        SettingMeetingTaskMode = 0x00000116,
        SettingInvisibleTaskMode = 0x00000117,
        PlainYes = 0x00000118,
        PlainNo = 0x00000119,
        PrivacyPolicyTitle = 0x0000011a,
        PrivacyPolicyText = 0x0000011b,
        ManageDataButton = 0x0000011c,
        UnderstandButton = 0x0000011d,
        HowToPlayText2Switch = 0x0000011e,
        ChatRateLimit = 0x0000011f,
        TotalTasksCompleted = 0x00000120,
        ServerNA = 0x00000121,
        ServerEU = 0x00000122,
        ServerAS = 0x00000123,
        ServerSA = 0x00000124,
        LangEnglish = 0x00000125,
        LangFrench = 0x00000126,
        LangItalian = 0x00000127,
        LangGerman = 0x00000128,
        LangSpanish = 0x00000129,
        LangSpanishLATAM = 0x0000012a,
        LangBrazPort = 0x0000012b,
        LangPort = 0x0000012c,
        LangRussian = 0x0000012d,
        LangJapanese = 0x0000012e,
        LangKorean = 0x0000012f,
        LangDutch = 0x00000130,
        LangFilipino = 0x00000131,
        PlayerName = 0x00000132,
        MyTablet = 0x00000133,
        Download = 0x00000134,
        DownloadComplete = 0x00000135,
        DownloadTestEstTimeS = 0x00000136,
        DownloadTestEstTimeMS = 0x00000137,
        DownloadTestEstTimeHMS = 0x00000138,
        DownloadTestEstTimeDHMS = 0x00000139,
        Upload = 0x0000013a,
        Headquarters = 0x0000013b,
        GrabCoffee = 0x0000013c,
        TakeBreak = 0x0000013d,
        DontNeedWait = 0x0000013e,
        DoSomethingElse = 0x0000013f,
        NodeTB = 0x00000140,
        NodeIRO = 0x00000141,
        NodeGI = 0x00000142,
        NodePD = 0x00000143,
        NodeCA = 0x00000144,
        NodeMLG = 0x00000145,
        Vending = 0x00000146,
        OtherLanguage = 0x00000147,
        ImposterAmtAny = 0x00000148,
        VitalsORGN = 0x00000149,
        VitalsBLUE = 0x0000014a,
        VitalsRED = 0x0000014b,
        VitalsBRWN = 0x0000014c,
        VitalsGRN = 0x0000014d,
        VitalsPINK = 0x0000014e,
        VitalsWHTE = 0x0000014f,
        VitalsYLOW = 0x00000150,
        VitalsBLAK = 0x00000151,
        VitalsPURP = 0x00000152,
        VitalsCYAN = 0x00000153,
        VitalsLIME = 0x00000154,
        VitalsOK = 0x00000155,
        VitalsDEAD = 0x00000156,
        VitalsDC = 0x00000157,
        ColorOrange = 0x00000158,
        ColorBlue = 0x00000159,
        ColorRed = 0x0000015a,
        ColorBrown = 0x0000015b,
        ColorGreen = 0x0000015c,
        ColorPink = 0x0000015d,
        ColorWhite = 0x0000015e,
        ColorYellow = 0x0000015f,
        ColorBlack = 0x00000160,
        ColorPurple = 0x00000161,
        ColorCyan = 0x00000162,
        ColorLime = 0x00000163,
        MedID = 0x00000164,
        MedC = 0x00000165,
        MedHT = 0x00000166,
        MedBT = 0x00000167,
        MedWT = 0x00000168,
        MedETA = 0x00000169,
        MedHello = 0x0000016a,
        PetFailFetchData = 0x0000016b,
        BadResult = 0x0000016c,
        More = 0x0000016d,
        Processing = 0x0000016e,
        ExitGame = 0x0000016f,
        WaitingForHost = 0x00000170,
        LeftGameError = 0x00000171,
        PlayerWasBannedBy = 0x00000172,
        PlayerWasKickedBy = 0x00000173,
        CamEast = 0x00000174,
        CamCentral = 0x00000175,
        CamNortheast = 0x00000176,
        CamSouth = 0x00000177,
        CamSouthwest = 0x00000178,
        CamNorthwest = 0x00000179,
        LoadingFailed = 0x0000017a,
        LobbySizeWarning = 0x0000017b,
        Okay = 0x0000017c,
        OkayDontShow = 0x0000017d,
        Nevermind = 0x0000017e,
        Dummy = 0x0000017f,
        Bad = 0x00000180,
        Status = 0x00000181,
        Fine = 0x00000182,
        OK = 0x00000183,
        PetTryOn = 0x00000184,
        SecondsAbbv = 0x00000185,
        SecurityLogsSystem = 0x00000186,
        SecurityCamsSystem = 0x00000187,
        AdminMapSystem = 0x00000188,
        VitalsSystem = 0x00000189,
        BanButton = 0x0000018a,
        KickButton = 0x0000018b,
        ReportButton = 0x0000018c,
        ReportConfirmation = 0x0000018d,
        ReportBadName = 0x0000018e,
        ReportBadChat = 0x0000018f,
        ReportHacking = 0x00000190,
        ReportHarassment = 0x00000191,
        ReportWhy = 0x00000192,
        Visor = 0x00000193,
        NamePlate = 0x00000194,
        Visors = 0x00000195,
        NamePlates = 0x00000196,
        Cosmicube = 0x00000197,
        Cosmicubes = 0x00000198,
        Activate = 0x00000199,
        Deactivate = 0x0000019a,
        Owned = 0x0000019b,
        Purchase = 0x0000019c,
        CosmicubeProgression = 0x0000019d,
        ViewCube = 0x0000019e,
        ConfirmPurchaseHeader = 0x0000019f,
        ConfirmPurchaseText = 0x000001a0,
        DeactivateCube = 0x000001a1,
        ActivateCube = 0x000001a2,
        Bundles = 0x000001a3,
        Stars = 0x000001a4,
        PurchasingLabel = 0x000001a5,
        MouseMovement = 0x000001a6,
        KeyboardOptions = 0x000001a7,
        RemapBindings = 0x000001a8,
        KeyboardBindingsHeader = 0x000001a9,
        PolishRuby = 0x000001f4,
        ResetBreakers = 0x000001f5,
        Decontaminate = 0x000001f6,
        MakeBurger = 0x000001f7,
        UnlockSafe = 0x000001f8,
        SortRecords = 0x000001f9,
        PutAwayPistols = 0x000001fa,
        FixShower = 0x000001fb,
        CleanToilet = 0x000001fc,
        DressMannequin = 0x000001fd,
        PickUpTowels = 0x000001fe,
        RewindTapes = 0x000001ff,
        StartFans = 0x00000200,
        DevelopPhotos = 0x00000201,
        GetBiggolSword = 0x00000202,
        PutAwayRifles = 0x00000203,
        StopCharles = 0x00000204,
        AuthLeftOkay = 0x00000205,
        AuthRightOkay = 0x00000206,
        AuthLeftActive = 0x00000207,
        AuthRightActive = 0x00000208,
        AuthLeftNotActive = 0x00000209,
        AuthRightNotActive = 0x0000020a,
        VaultRoom = 0x00000226,
        Cockpit = 0x00000227,
        Armory = 0x00000228,
        Kitchen = 0x00000229,
        ViewingDeck = 0x0000022a,
        HallOfPortraits = 0x0000022b,
        Medical = 0x0000022c,
        CargoBay = 0x0000022d,
        Ventilation = 0x0000022e,
        Showers = 0x0000022f,
        Engine = 0x00000230,
        Brig = 0x00000231,
        MeetingRoom = 0x00000232,
        Records = 0x00000233,
        Lounge = 0x00000234,
        GapRoom = 0x00000235,
        MainHall = 0x00000236,
        RevealCode = 0x00000237,
        DirtyHeader = 0x00000238,
        ErrorServerOverload = 0x000002bc,
        ErrorIntentionalLeaving = 0x000002bd,
        ErrorFocusLost = 0x000002be,
        ErrorBanned = 0x000002bf,
        ErrorKicked = 0x000002c0,
        ErrorBannedNoCode = 0x000002c1,
        ErrorKickedNoCode = 0x000002c2,
        ErrorHacking = 0x000002c3,
        ErrorFullGame = 0x000002c4,
        ErrorStartedGame = 0x000002c5,
        ErrorNotFoundGame = 0x000002c6,
        ErrorInactivity = 0x000002c7,
        ErrorGenericOnlineDisconnect = 0x000002c8,
        ErrorGenericLocalDisconnect = 0x000002c9,
        ErrorInvalidName = 0x000002ca,
        ErrorUnknown = 0x000002cb,
        ErrorIncorrectVersion = 0x000002cc,
        ErrorNotAuthenticated = 0x000002cd,
        ErrorInternalServer = 0x000002ce,
        ErrorPlatformLock = 0x000002cf,
        ErrorLobbyInactivity = 0x000002d0,
        ErrorMatchmakerInactivity = 0x000002d1,
        ErrorInvalidGameOptions = 0x000002d2,
        ErrorNoServersAvailable = 0x000002d3,
        ErrorQuickmatchDisabled = 0x000002d4,
        ErrorTooManyGames = 0x000002d5,
        ErrorDuplicateConnection = 0x000002d6,
        ErrorTooManyRequests = 0x000002d7,
        ErrorSanction = 0x000002d8,
        VentDirection = 0x000003e8,
        VentMove = 0x000003e9,
        MenuNavigate = 0x000003ea,
        NoTranslation = 0x000003eb,
        NsoError = 0x000003ec,
        RolesSettings = 0x000005dc,
        ScientistRole = 0x000005dd,
        EngineerRole = 0x000005de,
        GuardianAngelRole = 0x000005df,
        ShapeshifterRole = 0x000005e0,
        ScientistBlurb = 0x000005e1,
        EngineerBlurb = 0x000005e2,
        GuardianAngelBlurb = 0x000005e3,
        ShapeshifterBlurb = 0x000005e4,
        CrewmateBlurb = 0x000005e5,
        ImpostorBlurb = 0x000005e6,
        YourRoleIs = 0x000005e7,
        ShapeshiftAbility = 0x000005e8,
        VentAbility = 0x000005e9,
        VitalsAbility = 0x000005ea,
        ProtectAbility = 0x000005eb,
        ShapeshiftAbilityUndo = 0x000005ec,
        RoleChanceAndQuantity = 0x000005ed,
        ProtectedRecently = 0x000005ee,
        ShapeshifterDuration = 0x000005ef,
        ShapeshifterCooldown = 0x000005f0,
        ShapeshifterLeaveSkin = 0x000005f1,
        ScientistCooldown = 0x000005f2,
        GuardianAngelCooldown = 0x000005f3,
        EngineerCooldown = 0x000005f4,
        ScientistBlurbMed = 0x000005f5,
        ScientistBlurbLong = 0x000005f6,
        EngineerBlurbMed = 0x000005f7,
        EngineerBlurbLong = 0x000005f8,
        GuardianAngelBlurbMed = 0x000005f9,
        GuardianAngelBlurbLong = 0x000005fa,
        ShapeshifterBlurbMed = 0x000005fb,
        ShapeshifterBlurbLong = 0x000005fc,
        RoleHint = 0x000005fd,
        EngineerInVentCooldown = 0x000005fe,
        ScientistBatteryCharge = 0x000005ff,
        GuardianAngelDuration = 0x00000600,
        GuardianAngelImpostorSeeProtect = 0x00000601,
        StatsRoleWins = 0x00000602,
        StatsEngineerVents = 0x00000603,
        StatsScientistChargesGained = 0x00000604,
        StatsGuardianAngelCrewmatesProtected = 0x00000605,
        StatsShapeshifterShiftedKills = 0x00000606,
        CrewmateGhostRole = 0x00000607,
        ImpostorGhostRole = 0x00000608,
        HauntAbilityName = 0x00000609,
        SeekButton = 0x0000060a,
        SanctionDuration = 0x000006a4,
        SanctionPermanent = 0x000006a5,
        SanctionConduct = 0x000006a6,
        SanctionImpersonationCeleb = 0x000006a7,
        SanctionSpamming = 0x000006a8,
        SanctionInappropriateNameUnsportsmanlike = 0x000006a9,
        SanctionUnsportsmanlikeConduct = 0x000006aa,
        SanctionImpersonationDevelopers = 0x000006ab,
        SanctionInappropriateChatPersonalInfo = 0x000006ac,
        SanctionInappropriateNameDerogatory = 0x000006ad,
        SanctionInappropriateNameNsfw = 0x000006ae,
        SanctionBullying = 0x000006af,
        SanctionCheatingHacking = 0x000006b0,
        SanctionInappropriateChatDating = 0x000006b1,
        SanctionWeaponizingRules = 0x000006b2,
        SanctionRepeatOffender3 = 0x000006b3,
        SanctionSexualMisconduct = 0x000006b4,
        SanctionDoxing = 0x000006b5,
        SanctionIllegalActivity = 0x000006b6,
        SanctionHarassment = 0x000006b7,
        SanctionSelfHarmPromotion = 0x000006b8,
        SanctionRepeatOffender10 = 0x000006b9,
        SanctionUnknown = 0x000006ba,
        ScreenShakeOption = 0x0000076c,
        FeaturedItems = 0x0000076d,
        FeaturedBundles = 0x0000076e,
        FeaturedCubes = 0x0000076f,
        BugReportPopUpAttachScreenshotDesc = 0x00000770,
        UserIdTokenError = 0x00000771,
        NewGameMode = 0x00000772,
        NewModeInfo = 0x00000773,
        HideSeekHowToPlayTitleOne = 0x00000774,
        HideSeekHowToPlayCaptionOne = 0x00000775,
        HideSeekHowToPlayCaptionTwo = 0x00000776,
        HideSeekHowToPlayCaptionThree = 0x00000777,
        HideSeekHowToPlayPageOne = 0x00000778,
        HideSeekHowToPlayImpostorOne = 0x00000779,
        HideSeekHowToPlaySubtextOne = 0x0000077a,
        HideSeekHowToPlayCrewmateInfoOne = 0x0000077b,
        HideSeekHowToPlayCrewmateInfoTwo = 0x0000077c,
        HideSeekHowToPlayImpostorInfoOne = 0x0000077d,
        HideSeekHowToPlayFlashlightDefault = 0x0000077e,
        HideSeekHowToPlayFinalHide = 0x0000077f,
        HideSeekHowToPlayFlashlightMobile = 0x00000780,
        HideSeekHowToPlayFlashlightSwitch = 0x00000781,
        HideSeekHowToPlayFlashlightConsoles = 0x00000782,
        HideSeekHowToPlayFlashlightPlayStation = 0x00000783,
        QCLocationLaptop = 0x000007d0,
        QCLocationSkeld = 0x000007d1,
        QCLocationMira = 0x000007d2,
        QCLocationPolus = 0x000007d3,
        QCSystemsStart = 0x000007d4,
        QCSystemsKick = 0x000007d5,
        QCCrewI = 0x000007d6,
        QCCrewMe = 0x000007d7,
        QCCrewNoOne = 0x000007d8,
        QCAccAKilledB = 0x000007d9,
        QCAccAKilledBNeg = 0x000007da,
        QCAccAIsSuspicious = 0x000007db,
        QCAccAIsSuspiciousNeg = 0x000007dc,
        QCAccASawBVent = 0x000007dd,
        QCAccASawBVentNeg = 0x000007de,
        QCAccAWasChasingB = 0x000007df,
        QCAccAWasChasingBNeg = 0x000007e0,
        QCAccAIsLying = 0x000007e1,
        QCAccAIsLyingNeg = 0x000007e2,
        QCAccVoteA = 0x000007e3,
        QCAccVoteANeg = 0x000007e4,
        QCAccADidntReport = 0x000007e5,
        QCResYes = 0x000007e6,
        QCResNo = 0x000007e7,
        QCResDontKnow = 0x000007e8,
        QCResDontKnowNeg = 0x000007e9,
        QCResAWas = 0x000007ea,
        QCResAWasNeg = 0x000007eb,
        QCResADid = 0x000007ec,
        QCResADidNeg = 0x000007ed,
        QCResVote = 0x000007ee,
        QCResVoteNeg = 0x000007ef,
        QCResAWasAtB = 0x000007f0,
        QCResAWasAtBNeg = 0x000007f1,
        QCResRip = 0x000007f2,
        QCResRipNeg = 0x000007f3,
        QCResLies = 0x000007f4,
        QCResLiesNeg = 0x000007f5,
        QCQstWhere = 0x000007f6,
        QCQstWho = 0x000007f7,
        QCQstWhoWasWith = 0x000007f8,
        QCQstWhatWasADoing = 0x000007f9,
        QCQstWhoFixedA = 0x000007fa,
        QCQstWhereWasA = 0x000007fb,
        QCQstBodyOrMeeting = 0x000007fc,
        QCStaASawB = 0x000007fd,
        QCStaAWasWithB = 0x000007fe,
        QCStaADidB = 0x000007ff,
        QCStaASelfReported = 0x00000800,
        QCStaDoubleKill = 0x00000801,
        QCStaWasSelfReport = 0x00000802,
        QCStaPleaseDoTasks = 0x00000803,
        QCStaBodyWasInA = 0x00000804,
        QCStaACalledMeeting = 0x00000805,
        QCLocation = 0x00000806,
        QCSystems = 0x00000807,
        QCCrew = 0x00000808,
        QCAccusation = 0x00000809,
        QCResponse = 0x0000080a,
        QCQuestion = 0x0000080b,
        QCStatements = 0x0000080c,
        ANY = 0x0000080d,
        ChatType = 0x0000080e,
        QuickChatOnly = 0x0000080f,
        FreeChatOnly = 0x00000810,
        FreeOrQuickChat = 0x00000811,
        DateOfBirth = 0x00000812,
        DateOfBirthEnter = 0x00000813,
        Month = 0x00000814,
        Day = 0x00000815,
        Year = 0x00000816,
        January = 0x00000817,
        February = 0x00000818,
        March = 0x00000819,
        April = 0x0000081a,
        May = 0x0000081b,
        June = 0x0000081c,
        July = 0x0000081d,
        August = 0x0000081e,
        September = 0x0000081f,
        October = 0x00000820,
        November = 0x00000821,
        December = 0x00000822,
        Submit = 0x00000823,
        QCMore = 0x00000824,
        Success = 0x00000825,
        Failed = 0x00000826,
        ErrorCreate = 0x00000827,
        SuccessCreate = 0x00000828,
        Close = 0x00000829,
        ErrorLogIn = 0x0000082a,
        SuccessLogIn = 0x0000082b,
        AccountInfo = 0x0000082c,
        Account = 0x0000082d,
        UserName = 0x0000082e,
        Height = 0x0000082f,
        Weight = 0x00000830,
        SignIn = 0x00000831,
        CreateAccount = 0x00000832,
        RequestPermission = 0x00000833,
        RandomizeName = 0x00000834,
        AccountLinking = 0x00000835,
        ChangeName = 0x00000836,
        LogOut = 0x00000837,
        GuardianWait = 0x00000838,
        EmailEdit = 0x00000839,
        EmailResend = 0x0000083a,
        GuestContinue = 0x0000083b,
        GuardianEmailSent = 0x0000083c,
        GuardianCheckEmail = 0x0000083d,
        EditName = 0x0000083e,
        Name = 0x0000083f,
        CreateAccountQuestion = 0x00000840,
        DoYouWantCreate = 0x00000841,
        PermissionRequired = 0x00000842,
        NeedPermissionText = 0x00000843,
        GuardianEmailTitle = 0x00000844,
        Send = 0x00000845,
        NewEmail = 0x00000846,
        ConfirmEmail = 0x00000847,
        EditEmail = 0x00000848,
        Loading = 0x00000849,
        Welcome = 0x0000084a,
        DLLNotFoundAccountError = 0x0000084b,
        ContinueOffline = 0x0000084c,
        CreateTryAgain = 0x0000084d,
        WantToLogIn = 0x0000084e,
        GoOffline = 0x0000084f,
        PlayAsGuest = 0x00000850,
        LogInTitle = 0x00000851,
        LogInInfoText = 0x00000852,
        ShowAccountSupportID5 = 0x00000853,
        ShowAccountSupportID4 = 0x00000854,
        ShowAccountSupportID3 = 0x00000855,
        ShowAccountSupportID2 = 0x00000856,
        ShowAccountSupportID1 = 0x00000857,
        YouAreNotOnline = 0x00000858,
        SaveGameOutOfSpaceMessage = 0x00000859,
        SaveGameOutOfSpaceConfirm = 0x0000085a,
        SaveGameOutOfSpaceCancel = 0x0000085b,
        EngagementScreen = 0x0000085c,
        EngagementScreenSignIn = 0x0000085d,
        FollowUs = 0x0000085e,
        ColorMaroon = 0x0000085f,
        ColorRose = 0x00000860,
        ColorBanana = 0x00000861,
        ColorGray = 0x00000862,
        ColorTan = 0x00000863,
        ColorSunset = 0x00000864,
        QuickChatInstructionsStart = 0x00000865,
        QuickChatInstructionsChild = 0x00000866,
        QuickChatInstructionsGuest = 0x00000867,
        QuickChatInstructionsFull = 0x00000868,
        SwitchEShopBrowseAll = 0x00000869,
        ColorCoral = 0x0000086a,
        GuardianEmail = 0x0000086b,
        LocalButton = 0x0000086c,
        OnlineButton = 0x0000086d,
        HowToPlayButton = 0x0000086e,
        FreePlayButton = 0x0000086f,
        PublicHeader = 0x00000870,
        PrivateHeader = 0x00000871,
        HostHeader = 0x00000872,
        EmergencyMeeting = 0x00000873,
        BodyReported = 0x00000874,
        PlayAgain = 0x00000875,
        QuitLabel = 0x00000876,
        DownloadLabel = 0x00000877,
        UploadLabel = 0x00000878,
        TimeRemaining = 0x00000879,
        AnnouncementLabel = 0x0000087a,
        StartLabel = 0x0000087b,
        UseLabel = 0x0000087c,
        KillLabel = 0x0000087d,
        SabotageLabel = 0x0000087e,
        VentLabel = 0x0000087f,
        OptionsLabel = 0x00000880,
        ReportLabel = 0x00000881,
        CO2Label = 0x00000882,
        NutriLabel = 0x00000883,
        RADLabel = 0x00000884,
        WaterLabel = 0x00000885,
        DiscussLabel = 0x00000886,
        DeadLabel = 0x00000887,
        SkippedVoting = 0x00000888,
        ProceedLabel = 0x00000889,
        HolidayHatLabel = 0x0000088a,
        HatLabel = 0x0000088b,
        PetLabel = 0x0000088c,
        SkinLabel = 0x0000088d,
        DoorlogLabel = 0x0000088e,
        VitalsLabel = 0x0000088f,
        InsufficientStorageError = 0x00000890,
        NetworkError = 0x00000891,
        OtherDownloadError = 0x00000892,
        DownloadingLabel = 0x00000893,
        DownloadSizeLabel = 0x00000894,
        SkipVoteLabel = 0x00000895,
        LogInInfoTextSwitch = 0x00000896,
        WeatherDataDownload = 0x00000897,
        BeginLabel = 0x00000898,
        QuietLabel = 0x00000899,
        LogLabel = 0x0000089a,
        ReadingLabel = 0x0000089b,
        UploadingLabel = 0x0000089c,
        ConnectionLabel = 0x0000089d,
        GoodLabel = 0x0000089e,
        PoorLabel = 0x0000089f,
        NoneLabel = 0x000008a0,
        ProgressLabel = 0x000008a1,
        PerfectLabel = 0x000008a2,
        NoDeadBodiesFound = 0x000008a3,
        AirshipBundle = 0x000008a4,
        PolusBundle = 0x000008a5,
        PolusSkinBundle = 0x000008a6,
        MiraBundle = 0x000008a7,
        MiraSkinBundle = 0x000008a8,
        PetAlien2 = 0x000008a9,
        PetAlien1 = 0x000008aa,
        PetAnimal = 0x000008ab,
        PetCrewmate = 0x000008ac,
        PetStickmin = 0x000008ad,
        PrisonerSkin = 0x000008ae,
        Cyborg_RHM = 0x000008af,
        CCC_Officer = 0x000008b0,
        VentCleaning = 0x000008b1,
        CleanUp = 0x000008b2,
        ControllerDisconnectedMessage = 0x000008b3,
        TermsOfUseTitle = 0x000008b4,
        PPAndToUTitle = 0x000008b5,
        ComePlayDiscord = 0x000008b6,
        SupportEmail = 0x000008b7,
        SupportIDLabel = 0x000008b8,
        pk05_davehat = 0x000008b9,
        pk05_Ellie = 0x000008ba,
        pk05_Svenhat = 0x000008bb,
        pk05_Burthat = 0x000008bc,
        pk05_Ellryhat = 0x000008bd,
        pk05_monocles = 0x000008be,
        pk05_cheesetoppat = 0x000008bf,
        pk05_Macbethhat = 0x000008c0,
        pk05_HenryToppat = 0x000008c1,
        pk05_EllieToppat = 0x000008c2,
        pk05_GeoffreyToppat = 0x000008c3,
        InviteFriends = 0x000008c4,
        Continue = 0x000008c5,
        GameComplete = 0x000008c6,
        XpGained = 0x000008c7,
        PodsEarned = 0x000008c8,
        CosmicubeNodeUnlocked = 0x000008c9,
        LevelShorthand = 0x000008ca,
        PrestigeLevelShorthand = 0x000008cb,
        MaxLevel = 0x000008cc,
        EquipLabel = 0x000008cd,
        XpGainedValue = 0x000008ce,
        PSNErrorSessionFailed = 0x000008cf,
        PSNErrorSessionJoinFailed = 0x000008d0,
        PSNErrorSessionGetInfoFailed = 0x000008d1,
        PSNErrorPSNConnectionLost = 0x000008d2,
        PSNErrorUserSignedOut = 0x000008d3,
        CrossPlayTitle = 0x000008d4,
        CrossPlayAllPlatforms = 0x000008d5,
        CrossPlaySamePlatform = 0x000008d6,
        QuickChat = 0x000008d7,
        TimeOutText = 0x000008d8,
        RetryText = 0x000008d9,
        PlayerLevel = 0x000008da,
        PlayerXp = 0x000008db,
        PlayerLevelExtremeShorthand = 0x000008dc,
        Max = 0x000008dd,
        Wardrobe = 0x000008de,
        CopiedText = 0x000008df,
        LinkAccount = 0x000008e0,
        CreateNewAccount = 0x000008e1,
        LinkExistingAccount = 0x000008e2,
        LinkAccountExplanation = 0x000008e3,
        LinkAccountCode = 0x000008e4,
        ErrorLink = 0x000008e5,
        UnlinkAccount = 0x000008e6,
        ConfirmUnlinkAccount = 0x000008e7,
        UnlinkAccountExplain = 0x000008e8,
        UnlinkAccountExplainConfirm = 0x000008e9,
        UnlinkError = 0x000008ea,
        UnlinkSuccess = 0x000008eb,
        ConfirmLinkExistingAccount = 0x000008ec,
        LinkExistingAccountExplain = 0x000008ed,
        LinkExistingAccountExplainConfirm = 0x000008ee,
        ResetAccount = 0x000008ef,
        CrossPlayEnabledWarning = 0x000008f0,
        StoreComingSoon = 0x000008f1,
        Locked = 0x000008f2,
        FailPurchase = 0x000008f3,
        FailPurchaseUnknown = 0x000008f4,
        FailPurchaseAlreadyOwn = 0x000008f5,
        FailPurchaseCurrency = 0x000008f6,
        FailPurchaseCubeOwn = 0x000008f7,
        ErrorPlatformParentalControlsBlock = 0x000008f8,
        Crewmates = 0x000008f9,
        Colors = 0x000008fa,
        Active = 0x000008fb,
        Equipped = 0x000008fc,
        QCLocationAirship = 0x000008fd,
        XboxShopBrowseAll = 0x000008fe,
        PSShopBrowseAll = 0x000008ff,
        SteamNotInitialized = 0x00000900,
        LoggedInErrorStarPurchase = 0x00000901,
        StarDisclaimer = 0x00000902,
        HowToPlayText_Consoles = 0x00000903,
        ErrorQuickChatMode = 0x00000904,
        ErrorLobbyUsersBlocked = 0x00000905,
        ItchNoStars = 0x00000906,
        CheckingPurchasesLabel = 0x00000907,
        RedeemPurchasedItemsTitle = 0x00000908,
        RedeemPurcahsedItemsExplain = 0x00000909,
        RedeemProceed = 0x0000090a,
        RedeemNotYet = 0x0000090b,
        AccountIDDisplay = 0x0000090c,
        RedeemNever = 0x0000090d,
        AvailableFor = 0x0000090e,
        GuestProgressionWarning = 0x0000090f,
        ErrorSelfPlatformLock = 0x00000910,
        ErrorCrossPlat = 0x00000911,
        SettingsStreamerMode = 0x00000912,
        RoomCodeInfo = 0x00000913,
        AbbreviatedDay = 0x00000914,
        AbbreviatedHour = 0x00000915,
        AbbreviatedMinute = 0x00000916,
        AbbreviatedSecond = 0x00000917,
        MaxVentUses = 0x00000a8c,
        MaxTimeInVent = 0x00000a8d,
        MinCrewmatesForVitals = 0x00000a8e,
        EscapeTime = 0x00000a8f,
        AllTasksComplete = 0x00000a90,
        EscapePrompt = 0x00000a91,
        CrewmateFlashlightSize = 0x00000a92,
        ImpostorFlashlightSize = 0x00000a93,
        CrewmateLeadTime = 0x00000a94,
        CrewmadeHideBlurb = 0x00000a95,
        ImpostorKillBlurb = 0x00000a96,
        HideCountdown = 0x00000a97,
        ScaryMusicDistance = 0x00000a98,
        ShortTaskTimeValue = 0x00000a99,
        LongTaskTimeValue = 0x00000a9a,
        CommonTaskTimeValue = 0x00000a9b,
        UseFlashlight = 0x00000a9c,
        FinalEscapeTime = 0x00000a9d,
        VeryScaryMusicDistance = 0x00000a9e,
        SeekerFinalSpeed = 0x00000a9f,
        SeekerFinalVents = 0x00000aa0,
        SeekerFinalMap = 0x00000aa1,
        CrewmateVentCooldown = 0x00000aa2,
        SeekerPings = 0x00000aa3,
        MaxPingTime = 0x00000aa4,
        ShowPingTime = 0x00000aa5,
        MinPingTime = 0x00000aa6,
        ShowCrewmateNames = 0x00000aa7,
        ShowImpostorNames = 0x00000aa8,
        HideActionButton = 0x00000aa9,
        RuleOneCrewmates = 0x00000aaa,
        RuleTwoCrewmates = 0x00000aab,
        RuleThreeCrewmates = 0x00000aac,
        RuleOneImpostor = 0x00000aad,
        RuleTwoImpostor = 0x00000aae,
        RuleThreeImpostor = 0x00000aaf,
        RuleOneCrewmatesTitle = 0x00000ab0,
        RuleTwoCrewmatesTitle = 0x00000ab1,
        RuleThreeCrewmatesTitle = 0x00000ab2,
        RuleOneImpostorTitle = 0x00000ab3,
        RuleTwoImpostorTitle = 0x00000ab4,
        RoundRobin = 0x00000ab5,
        OptionUnavailablePublicLobby = 0x00000ab6,
        StatsHidenSeekGamesCrewmateSurvived = 0x00000ab7,
        StatsHidenSeekTimesVented = 0x00000ab8,
        StatsTimesPettedPet = 0x00000ab9,
        StatsImpostorKills_HideAndSeek = 0x00000aba,
        StatsFastestCrewmateWin_HideAndSeek = 0x00000abb,
        StatsFastestImpostorWin_HideAndSeek = 0x00000abc,
        StatsHideAndSeekImpostorVictory = 0x00000abd,
        StatsHideAndSeekCrewmateVictory = 0x00000abe,
        AmongUsFriends = 0x00000af0,
        FriendsGuestWarning = 0x00000af1,
        PlatformFriends = 0x00000af2,
        BlockedPlayers = 0x00000af3,
        RecentPlayers = 0x00000af4,
        LobbyLabel = 0x00000af5,
        FriendCodeExplanation = 0x00000af6,
        FriendCodeSuccess = 0x00000af7,
        FriendRequestReceived = 0x00000af8,
        FriendRequestSent = 0x00000af9,
        GameLobbyInviteSent = 0x00000afa,
        GameLobbyInviteReceived = 0x00000afb,
        BlockPlayerConfirm = 0x00000afc,
        RemoveFriendConfirm = 0x00000afd,
        InviteToLobbyConfirm = 0x00000afe,
        FriendCodeLabel = 0x00000aff,
        FriendCodeCreationTitle = 0x00000b00,
        FriendRequestSentFailed = 0x00000b01,
        ErrorBadUsername = 0x00000b02,
        ErrorUserNotFound = 0x00000b03,
        ErrorThisIsYou = 0x00000b04,
        ErrorFriendRequestExists = 0x00000b05,
        ErrorAlreadyFriends = 0x00000b06,
        GameLobbyInviteSentFailed = 0x00000b07,
        BlockedPlayerFailed = 0x00000b08,
        BlockedPlayer = 0x00000b09,
        AlreadyBlocked = 0x00000b0a,
        FriendList = 0x00000b0b,
        NoNewRequests = 0x00000b0c,
        AddFriendPrompt = 0x00000b0d,
        NewRequests = 0x00000b0e,
        Requests = 0x00000b0f,
        AddFriend = 0x00000b10,
        StreamWarning = 0x00000b11,
        FriendsListPermissionsWarning = 0x00000b12,
        AddFriendConfirm = 0x00000b13,
        UnfriendConfirm = 0x00000b14,
        UnblockConfirm = 0x00000b15,
        SettingsEnableFriendInvites = 0x00000b16,
        ErrorCrossPlatformCommunication = 0x00000b17,
        ErrorPlatformFriends = 0x00000b18,
        ErrorPlayerBlockedYou = 0x00000b19,
        ErrorRecipientMaxFriendRequests = 0x00000b1a,
        ErrorSenderMaxFriendRequests = 0x00000b1b,
        ErrorMaxFriends = 0x00000b1c,
        ErrorRecipientMaxFriends = 0x00000b1d,
        ParentPortalButton = 0x00000b1e,
        FriendsListEmailSent = 0x00000b1f,
        AndroidAssetBundleWarning = 0x00000b20,
        FreeChatLinkWarning = 0x00000b21,
        FriendListUnavailable = 0x00000b22,
        SignInIssueTitle = 0x00000b23,
        SignInIssueText = 0x00000b24,
        Ghost = 0x00000b25,
        CurrentlyHaunting = 0x00000b26,
        RestorePurchases = 0x00000b27,
        QCAccIsRole = 0x00000bb8,
        QCAccIsRoleNeg = 0x00000bb9,
        QCAccShapeshited = 0x00000bba,
        QCStaShapeshifterSkin = 0x00000bbb,
        QCResIsBeingFramed = 0x00000bbc,
        QCResIsRoleMaybe = 0x00000bbd,
        QCResCloseTo = 0x00000bbe,
        QCResProtected = 0x00000bbf,
        QCRoles = 0x00000bc0,
        ErrorFailedToCreateGame = 0x00000bc1,
        ErrorFailedToJoinCreatedGame = 0x00000bc2,
        ErrorDisconnectBeforeJoining = 0x00000bc3,
        ErrorDisconnectPacket = 0x00000bc4,
        PSEULA_SIEA = 0x00000bc5,
        PSEULA_SIEE = 0x00000bc6,
        ShowAccountID = 0x00000bc7,
        HideAccountID = 0x00000bc8,
        HiddenAccountID = 0x00000bc9,
        ErrorLobbyFailedGettingBlockedUsers = 0x00000bca,
        SteamOverlayDisabled = 0x00000bcb,
        QCOnlyInfo = 0x00000bcc,
        FreeChatInfo = 0x00000bcd,
        FreeChatWarning = 0x00000bce,
        TryAgain = 0x00000bcf,
        TempDisabled = 0x00000bd0,
        TempDisabledLinkExplain = 0x00000bd1,
        RedeemPopup = 0x00000bd2,
        RedeemButton = 0x00000bd3,
        Decontamination3 = 0x00000bd4,
        MergeGuestAccountText = 0x00000bd5,
        MergeGuestAccountTitle = 0x00000bd6,
        ErrorCommunications = 0x00000bd7,
        ManageAccountTitle = 0x00000bd8,
        ManageAccountText = 0x00000bd9,
        Email = 0x00000bda,
        BugReportPopUpSubmittedText = 0x00000bdb,
        BugReportPopUpCategoryLabel = 0x00000bdc,
        BugReportPopUpDescriptionLabel = 0x00000bdd,
        BugReportPopUpTitle = 0x00000bde,
        BugReportCategoryServerIssues = 0x00000bdf,
        BugReportCategoryGameplayIssue = 0x00000be0,
        BugReportCategoryAccountManagement = 0x00000be1,
        BugReportCategoryBilling = 0x00000be2,
        BugReportCategoryGeneral = 0x00000be3,
        BugReportIssueButton = 0x00000be4,
        BugReportPopUpSubmissionFailedText = 0x00000be5,
        BugReportPopUpAttachScreenshotLabel = 0x00000be6,
        SettingsColorblind = 0x00000c80,
        SettingsHelp = 0x00000c81,
        SecLogEntryColorblind = 0x00000c82,
        DeleteAccount = 0x00000c83,
        DoNotDeleteAccount = 0x00000c84,
        AccountDeleteHelp = 0x00000c85,
        AccountUnDeleteHelp = 0x00000c86,
        ConfirmDelete = 0x00000c87,
        ConfirmDeleteAccounts = 0x00000c88,
        ConfirmDeleteAccountsEmpty = 0x00000c89,
        AccountRequestDelete = 0x00000c8a,
        HasBeenKilled = 0x00000c8b,
        GameType = 0x00000dac,
        GameTypeError = 0x00000dad,
        GameTypeClassic = 0x00000dae,
        GameTypeHideAndSeek = 0x00000daf,
        PetAction = 0x00000db0,
        CreateLabel = 0x00000db1,
        TagFiltersTitle = 0x00000db2,
        TagFiltersHelpFindGame = 0x00000db3,
        TagFiltersHelpCreate = 0x00000db4,
        TagsFilteredSingular = 0x00000db5,
        TagsFilteredPlural = 0x00000db6,
        TagsAppliedSingular = 0x00000db7,
        TagsAppliedPlural = 0x00000db8,
        DefaultFilterTag_FirstTime = 0x00000db9,
        DefaultFilterTag_Casual = 0x00000dba,
        DefaultFilterTag_Serious = 0x00000dbb,
        DefaultFilterTag_Expert = 0x00000dbc,
    };

#else
    enum StringNames__Enum {
        StringNames__Enum_ExitButton = 0x00000000,
        StringNames__Enum_BackButton = 0x00000001,
        StringNames__Enum_AvailableGamesLabel = 0x00000002,
        StringNames__Enum_CreateGameButton = 0x00000003,
        StringNames__Enum_FindGameButton = 0x00000004,
        StringNames__Enum_EnterCode = 0x00000005,
        StringNames__Enum_GhostIgnoreTasks = 0x00000006,
        StringNames__Enum_GhostDoTasks = 0x00000007,
        StringNames__Enum_GhostImpostor = 0x00000008,
        StringNames__Enum_ImpostorTask = 0x00000009,
        StringNames__Enum_FakeTasks = 0x0000000a,
        StringNames__Enum_TaskComplete = 0x0000000b,
        StringNames__Enum_ExileTextSP = 0x0000000c,
        StringNames__Enum_ExileTextSN = 0x0000000d,
        StringNames__Enum_ExileTextPP = 0x0000000e,
        StringNames__Enum_ExileTextPN = 0x0000000f,
        StringNames__Enum_NoExileSkip = 0x00000010,
        StringNames__Enum_NoExileTie = 0x00000011,
        StringNames__Enum_ImpostorsRemainS = 0x00000012,
        StringNames__Enum_ImpostorsRemainP = 0x00000013,
        StringNames__Enum_Hallway = 0x00000014,
        StringNames__Enum_Storage = 0x00000015,
        StringNames__Enum_Cafeteria = 0x00000016,
        StringNames__Enum_Reactor = 0x00000017,
        StringNames__Enum_UpperEngine = 0x00000018,
        StringNames__Enum_Nav = 0x00000019,
        StringNames__Enum_Admin = 0x0000001a,
        StringNames__Enum_Electrical = 0x0000001b,
        StringNames__Enum_LifeSupp = 0x0000001c,
        StringNames__Enum_Shields = 0x0000001d,
        StringNames__Enum_MedBay = 0x0000001e,
        StringNames__Enum_Security = 0x0000001f,
        StringNames__Enum_Weapons = 0x00000020,
        StringNames__Enum_LowerEngine = 0x00000021,
        StringNames__Enum_Comms = 0x00000022,
        StringNames__Enum_Decontamination = 0x00000023,
        StringNames__Enum_Launchpad = 0x00000024,
        StringNames__Enum_LockerRoom = 0x00000025,
        StringNames__Enum_Laboratory = 0x00000026,
        StringNames__Enum_Balcony = 0x00000027,
        StringNames__Enum_Office = 0x00000028,
        StringNames__Enum_Greenhouse = 0x00000029,
        StringNames__Enum_DivertPowerTo = 0x0000002a,
        StringNames__Enum_AcceptDivertedPower = 0x0000002b,
        StringNames__Enum_SubmitScan = 0x0000002c,
        StringNames__Enum_PrimeShields = 0x0000002d,
        StringNames__Enum_FuelEngines = 0x0000002e,
        StringNames__Enum_ChartCourse = 0x0000002f,
        StringNames__Enum_StartReactor = 0x00000030,
        StringNames__Enum_SwipeCard = 0x00000031,
        StringNames__Enum_ClearAsteroids = 0x00000032,
        StringNames__Enum_UploadData = 0x00000033,
        StringNames__Enum_DownloadData = 0x00000034,
        StringNames__Enum_InspectSample = 0x00000035,
        StringNames__Enum_EmptyChute = 0x00000036,
        StringNames__Enum_EmptyGarbage = 0x00000037,
        StringNames__Enum_AlignEngineOutput = 0x00000038,
        StringNames__Enum_FixWiring = 0x00000039,
        StringNames__Enum_CalibrateDistributor = 0x0000003a,
        StringNames__Enum_UnlockManifolds = 0x0000003b,
        StringNames__Enum_ResetReactor = 0x0000003c,
        StringNames__Enum_FixLights = 0x0000003d,
        StringNames__Enum_FixComms = 0x0000003e,
        StringNames__Enum_RestoreOxy = 0x0000003f,
        StringNames__Enum_CleanO2Filter = 0x00000040,
        StringNames__Enum_StabilizeSteering = 0x00000041,
        StringNames__Enum_AssembleArtifact = 0x00000042,
        StringNames__Enum_SortSamples = 0x00000043,
        StringNames__Enum_MeasureWeather = 0x00000044,
        StringNames__Enum_EnterIdCode = 0x00000045,
        StringNames__Enum_HowToPlayText1 = 0x00000046,
        StringNames__Enum_HowToPlayText2 = 0x00000047,
        StringNames__Enum_HowToPlayText5 = 0x00000048,
        StringNames__Enum_HowToPlayText6 = 0x00000049,
        StringNames__Enum_HowToPlayText7 = 0x0000004a,
        StringNames__Enum_HowToPlayText81 = 0x0000004b,
        StringNames__Enum_HowToPlayText82 = 0x0000004c,
        StringNames__Enum_NumImpostorsS = 0x0000004d,
        StringNames__Enum_NumImpostorsP = 0x0000004e,
        StringNames__Enum_Crewmate = 0x0000004f,
        StringNames__Enum_Impostor = 0x00000050,
        StringNames__Enum_Victory = 0x00000051,
        StringNames__Enum_Defeat = 0x00000052,
        StringNames__Enum_CrewmatesDisconnected = 0x00000053,
        StringNames__Enum_ImpostorDisconnected = 0x00000054,
        StringNames__Enum_HowToPlayText41 = 0x00000055,
        StringNames__Enum_HowToPlayText42 = 0x00000056,
        StringNames__Enum_HowToPlayText43 = 0x00000057,
        StringNames__Enum_HowToPlayText44 = 0x00000058,
        StringNames__Enum_HowToPlayTextMap = 0x00000059,
        StringNames__Enum_HowToPlayTextCrew1 = 0x0000005a,
        StringNames__Enum_HowToPlayTextCrew2 = 0x0000005b,
        StringNames__Enum_HowToPlayTextCrew3 = 0x0000005c,
        StringNames__Enum_HowToPlayTextCrew4 = 0x0000005d,
        StringNames__Enum_HowToPlayTextCrew5 = 0x0000005e,
        StringNames__Enum_HowToPlayTextCrew6 = 0x0000005f,
        StringNames__Enum_HowToPlayTextImp1 = 0x00000060,
        StringNames__Enum_HowToPlayTextImp2 = 0x00000061,
        StringNames__Enum_HowToPlayTextImp3 = 0x00000062,
        StringNames__Enum_HowToPlayTextImp4 = 0x00000063,
        StringNames__Enum_HowToPlayTextImp5 = 0x00000064,
        StringNames__Enum_HowToPlayTextImp6 = 0x00000065,
        StringNames__Enum_HowToPlayTextImp7 = 0x00000066,
        StringNames__Enum_SettingsGeneral = 0x00000067,
        StringNames__Enum_SettingsControls = 0x00000068,
        StringNames__Enum_SettingsSound = 0x00000069,
        StringNames__Enum_SettingsGraphics = 0x0000006a,
        StringNames__Enum_SettingsData = 0x0000006b,
        StringNames__Enum_SettingsCensorChat = 0x0000006c,
        StringNames__Enum_SettingsMusic = 0x0000006d,
        StringNames__Enum_SettingsSFX = 0x0000006e,
        StringNames__Enum_SettingsOn = 0x0000006f,
        StringNames__Enum_SettingsOff = 0x00000070,
        StringNames__Enum_SettingsSendTelemetry = 0x00000071,
        StringNames__Enum_SettingsControlMode = 0x00000072,
        StringNames__Enum_SettingsTouchMode = 0x00000073,
        StringNames__Enum_SettingsJoystickMode = 0x00000074,
        StringNames__Enum_SettingsKeyboardMode = 0x00000075,
        StringNames__Enum_SettingsFullscreen = 0x00000076,
        StringNames__Enum_SettingsResolution = 0x00000077,
        StringNames__Enum_SettingsApply = 0x00000078,
        StringNames__Enum_SettingsPersonalizeAds = 0x00000079,
        StringNames__Enum_SettingsLanguage = 0x0000007a,
        StringNames__Enum_SettingsJoystickSize = 0x0000007b,
        StringNames__Enum_SettingsMouseMode = 0x0000007c,
        StringNames__Enum_PlayerColor = 0x0000007d,
        StringNames__Enum_PlayerHat = 0x0000007e,
        StringNames__Enum_PlayerSkin = 0x0000007f,
        StringNames__Enum_PlayerPet = 0x00000080,
        StringNames__Enum_GameSettings = 0x00000081,
        StringNames__Enum_GameRecommendedSettings = 0x00000082,
        StringNames__Enum_GameCustomSettings = 0x00000083,
        StringNames__Enum_GameMapName = 0x00000084,
        StringNames__Enum_GameNumImpostors = 0x00000085,
        StringNames__Enum_GameNumMeetings = 0x00000086,
        StringNames__Enum_GameDiscussTime = 0x00000087,
        StringNames__Enum_GameVotingTime = 0x00000088,
        StringNames__Enum_GamePlayerSpeed = 0x00000089,
        StringNames__Enum_GameCrewLight = 0x0000008a,
        StringNames__Enum_GameImpostorLight = 0x0000008b,
        StringNames__Enum_GameKillCooldown = 0x0000008c,
        StringNames__Enum_GameKillDistance = 0x0000008d,
        StringNames__Enum_GameCommonTasks = 0x0000008e,
        StringNames__Enum_GameLongTasks = 0x0000008f,
        StringNames__Enum_GameShortTasks = 0x00000090,
        StringNames__Enum_MatchMapName = 0x00000091,
        StringNames__Enum_MatchLanguage = 0x00000092,
        StringNames__Enum_MatchImpostors = 0x00000093,
        StringNames__Enum_MatchMaxPlayers = 0x00000094,
        StringNames__Enum_Cancel = 0x00000095,
        StringNames__Enum_Confirm = 0x00000096,
        StringNames__Enum_Limit = 0x00000097,
        StringNames__Enum_RoomCode = 0x00000098,
        StringNames__Enum_LeaveGame = 0x00000099,
        StringNames__Enum_ReturnToGame = 0x0000009a,
        StringNames__Enum_LocalHelp = 0x0000009b,
        StringNames__Enum_OnlineHelp = 0x0000009c,
        StringNames__Enum_SettingsVSync = 0x0000009d,
        StringNames__Enum_EmergencyCount = 0x0000009e,
        StringNames__Enum_EmergencyNotReady = 0x0000009f,
        StringNames__Enum_EmergencyDuringCrisis = 0x000000a0,
        StringNames__Enum_EmergencyRequested = 0x000000a1,
        StringNames__Enum_GameEmergencyCooldown = 0x000000a2,
        StringNames__Enum_BuyBeverage = 0x000000a3,
        StringNames__Enum_WeatherEta = 0x000000a4,
        StringNames__Enum_WeatherComplete = 0x000000a5,
        StringNames__Enum_ProcessData = 0x000000a6,
        StringNames__Enum_RunDiagnostics = 0x000000a7,
        StringNames__Enum_WaterPlants = 0x000000a8,
        StringNames__Enum_PickAnomaly = 0x000000a9,
        StringNames__Enum_WaterPlantsGetCan = 0x000000aa,
        StringNames__Enum_AuthOfficeOkay = 0x000000ab,
        StringNames__Enum_AuthCommsOkay = 0x000000ac,
        StringNames__Enum_AuthOfficeActive = 0x000000ad,
        StringNames__Enum_AuthCommsActive = 0x000000ae,
        StringNames__Enum_AuthOfficeNotActive = 0x000000af,
        StringNames__Enum_AuthCommsNotActive = 0x000000b0,
        StringNames__Enum_SecLogEntry = 0x000000b1,
        StringNames__Enum_EnterName = 0x000000b2,
        StringNames__Enum_SwipeCardPleaseSwipe = 0x000000b3,
        StringNames__Enum_SwipeCardBadRead = 0x000000b4,
        StringNames__Enum_SwipeCardTooFast = 0x000000b5,
        StringNames__Enum_SwipeCardTooSlow = 0x000000b6,
        StringNames__Enum_SwipeCardAccepted = 0x000000b7,
        StringNames__Enum_ReactorHoldToStop = 0x000000b8,
        StringNames__Enum_ReactorWaiting = 0x000000b9,
        StringNames__Enum_ReactorNominal = 0x000000ba,
        StringNames__Enum_MeetingWhoIsTitle = 0x000000bb,
        StringNames__Enum_MeetingVotingBegins = 0x000000bc,
        StringNames__Enum_MeetingVotingEnds = 0x000000bd,
        StringNames__Enum_MeetingVotingResults = 0x000000be,
        StringNames__Enum_MeetingProceeds = 0x000000bf,
        StringNames__Enum_MeetingHasVoted = 0x000000c0,
        StringNames__Enum_DataPolicyTitle = 0x000000c1,
        StringNames__Enum_DataPolicyText = 0x000000c2,
        StringNames__Enum_DataPolicyWhat = 0x000000c3,
        StringNames__Enum_AdPolicyTitle = 0x000000c4,
        StringNames__Enum_AdPolicyText = 0x000000c5,
        StringNames__Enum_Accept = 0x000000c6,
        StringNames__Enum_RemoveAds = 0x000000c7,
        StringNames__Enum_SwipeCardPleaseInsert = 0x000000c8,
        StringNames__Enum_LogNorth = 0x000000c9,
        StringNames__Enum_LogSouthEast = 0x000000ca,
        StringNames__Enum_LogSouthWest = 0x000000cb,
        StringNames__Enum_SettingShort = 0x000000cc,
        StringNames__Enum_SettingMedium = 0x000000cd,
        StringNames__Enum_SettingLong = 0x000000ce,
        StringNames__Enum_SamplesPress = 0x000000cf,
        StringNames__Enum_SamplesAdding = 0x000000d0,
        StringNames__Enum_SamplesSelect = 0x000000d1,
        StringNames__Enum_SamplesThanks = 0x000000d2,
        StringNames__Enum_SamplesComplete = 0x000000d3,
        StringNames__Enum_AstDestroyed = 0x000000d4,
        StringNames__Enum_TaskTestTitle = 0x000000d5,
        StringNames__Enum_BeginDiagnostics = 0x000000d6,
        StringNames__Enum_UserLeftGame = 0x000000d7,
        StringNames__Enum_GameStarting = 0x000000d8,
        StringNames__Enum_Tasks = 0x000000d9,
        StringNames__Enum_StatsTitle = 0x000000da,
        StringNames__Enum_StatsBodiesReported = 0x000000db,
        StringNames__Enum_StatsEmergenciesCalled = 0x000000dc,
        StringNames__Enum_StatsTasksCompleted = 0x000000dd,
        StringNames__Enum_StatsAllTasksCompleted = 0x000000de,
        StringNames__Enum_StatsSabotagesFixed = 0x000000df,
        StringNames__Enum_StatsImpostorKills = 0x000000e0,
        StringNames__Enum_StatsTimesMurdered = 0x000000e1,
        StringNames__Enum_StatsTimesEjected = 0x000000e2,
        StringNames__Enum_StatsCrewmateStreak = 0x000000e3,
        StringNames__Enum_StatsGamesImpostor = 0x000000e4,
        StringNames__Enum_StatsGamesCrewmate = 0x000000e5,
        StringNames__Enum_StatsGamesStarted = 0x000000e6,
        StringNames__Enum_StatsGamesFinished = 0x000000e7,
        StringNames__Enum_StatsImpostorVoteWins = 0x000000e8,
        StringNames__Enum_StatsImpostorKillsWins = 0x000000e9,
        StringNames__Enum_StatsImpostorSabotageWins = 0x000000ea,
        StringNames__Enum_StatsCrewmateVoteWins = 0x000000eb,
        StringNames__Enum_StatsCrewmateTaskWins = 0x000000ec,
        StringNames__Enum_MedscanRequested = 0x000000ed,
        StringNames__Enum_MedscanWaitingFor = 0x000000ee,
        StringNames__Enum_MedscanCompleted = 0x000000ef,
        StringNames__Enum_MedscanCompleteIn = 0x000000f0,
        StringNames__Enum_MonitorOxygen = 0x000000f1,
        StringNames__Enum_StoreArtifacts = 0x000000f2,
        StringNames__Enum_FillCanisters = 0x000000f3,
        StringNames__Enum_FixWeatherNode = 0x000000f4,
        StringNames__Enum_InsertKeys = 0x000000f5,
        StringNames__Enum_ResetSeismic = 0x000000f6,
        StringNames__Enum_SeismicHoldToStop = 0x000000f7,
        StringNames__Enum_SeismicNominal = 0x000000f8,
        StringNames__Enum_ScanBoardingPass = 0x000000f9,
        StringNames__Enum_OpenWaterways = 0x000000fa,
        StringNames__Enum_ReplaceWaterJug = 0x000000fb,
        StringNames__Enum_RepairDrill = 0x000000fc,
        StringNames__Enum_AlignTelescope = 0x000000fd,
        StringNames__Enum_RecordTemperature = 0x000000fe,
        StringNames__Enum_RebootWifi = 0x000000ff,
        StringNames__Enum_WifiRebootRequired = 0x00000100,
        StringNames__Enum_WifiPleasePowerOn = 0x00000101,
        StringNames__Enum_WifiPleaseWait = 0x00000102,
        StringNames__Enum_WifiPleaseReturnIn = 0x00000103,
        StringNames__Enum_WifiRebootComplete = 0x00000104,
        StringNames__Enum_Outside = 0x00000105,
        StringNames__Enum_GameSecondsAbbrev = 0x00000106,
        StringNames__Enum_Engines = 0x00000107,
        StringNames__Enum_Dropship = 0x00000108,
        StringNames__Enum_Decontamination2 = 0x00000109,
        StringNames__Enum_Specimens = 0x0000010a,
        StringNames__Enum_BoilerRoom = 0x0000010b,
        StringNames__Enum_GameOverImpostorDead = 0x0000010c,
        StringNames__Enum_GameOverImpostorKills = 0x0000010d,
        StringNames__Enum_GameOverTaskWin = 0x0000010e,
        StringNames__Enum_GameOverSabotage = 0x0000010f,
        StringNames__Enum_GameConfirmImpostor = 0x00000110,
        StringNames__Enum_GameVisualTasks = 0x00000111,
        StringNames__Enum_ExileTextNonConfirm = 0x00000112,
        StringNames__Enum_GameAnonymousVotes = 0x00000113,
        StringNames__Enum_GameTaskBarMode = 0x00000114,
        StringNames__Enum_SettingNormalTaskMode = 0x00000115,
        StringNames__Enum_SettingMeetingTaskMode = 0x00000116,
        StringNames__Enum_SettingInvisibleTaskMode = 0x00000117,
        StringNames__Enum_PlainYes = 0x00000118,
        StringNames__Enum_PlainNo = 0x00000119,
        StringNames__Enum_PrivacyPolicyTitle = 0x0000011a,
        StringNames__Enum_PrivacyPolicyText = 0x0000011b,
        StringNames__Enum_ManageDataButton = 0x0000011c,
        StringNames__Enum_UnderstandButton = 0x0000011d,
        StringNames__Enum_HowToPlayText2Switch = 0x0000011e,
        StringNames__Enum_ChatRateLimit = 0x0000011f,
        StringNames__Enum_TotalTasksCompleted = 0x00000120,
        StringNames__Enum_ServerNA = 0x00000121,
        StringNames__Enum_ServerEU = 0x00000122,
        StringNames__Enum_ServerAS = 0x00000123,
        StringNames__Enum_ServerSA = 0x00000124,
        StringNames__Enum_LangEnglish = 0x00000125,
        StringNames__Enum_LangFrench = 0x00000126,
        StringNames__Enum_LangItalian = 0x00000127,
        StringNames__Enum_LangGerman = 0x00000128,
        StringNames__Enum_LangSpanish = 0x00000129,
        StringNames__Enum_LangSpanishLATAM = 0x0000012a,
        StringNames__Enum_LangBrazPort = 0x0000012b,
        StringNames__Enum_LangPort = 0x0000012c,
        StringNames__Enum_LangRussian = 0x0000012d,
        StringNames__Enum_LangJapanese = 0x0000012e,
        StringNames__Enum_LangKorean = 0x0000012f,
        StringNames__Enum_LangDutch = 0x00000130,
        StringNames__Enum_LangFilipino = 0x00000131,
        StringNames__Enum_PlayerName = 0x00000132,
        StringNames__Enum_MyTablet = 0x00000133,
        StringNames__Enum_Download = 0x00000134,
        StringNames__Enum_DownloadComplete = 0x00000135,
        StringNames__Enum_DownloadTestEstTimeS = 0x00000136,
        StringNames__Enum_DownloadTestEstTimeMS = 0x00000137,
        StringNames__Enum_DownloadTestEstTimeHMS = 0x00000138,
        StringNames__Enum_DownloadTestEstTimeDHMS = 0x00000139,
        StringNames__Enum_Upload = 0x0000013a,
        StringNames__Enum_Headquarters = 0x0000013b,
        StringNames__Enum_GrabCoffee = 0x0000013c,
        StringNames__Enum_TakeBreak = 0x0000013d,
        StringNames__Enum_DontNeedWait = 0x0000013e,
        StringNames__Enum_DoSomethingElse = 0x0000013f,
        StringNames__Enum_NodeTB = 0x00000140,
        StringNames__Enum_NodeIRO = 0x00000141,
        StringNames__Enum_NodeGI = 0x00000142,
        StringNames__Enum_NodePD = 0x00000143,
        StringNames__Enum_NodeCA = 0x00000144,
        StringNames__Enum_NodeMLG = 0x00000145,
        StringNames__Enum_Vending = 0x00000146,
        StringNames__Enum_OtherLanguage = 0x00000147,
        StringNames__Enum_ImposterAmtAny = 0x00000148,
        StringNames__Enum_VitalsORGN = 0x00000149,
        StringNames__Enum_VitalsBLUE = 0x0000014a,
        StringNames__Enum_VitalsRED = 0x0000014b,
        StringNames__Enum_VitalsBRWN = 0x0000014c,
        StringNames__Enum_VitalsGRN = 0x0000014d,
        StringNames__Enum_VitalsPINK = 0x0000014e,
        StringNames__Enum_VitalsWHTE = 0x0000014f,
        StringNames__Enum_VitalsYLOW = 0x00000150,
        StringNames__Enum_VitalsBLAK = 0x00000151,
        StringNames__Enum_VitalsPURP = 0x00000152,
        StringNames__Enum_VitalsCYAN = 0x00000153,
        StringNames__Enum_VitalsLIME = 0x00000154,
        StringNames__Enum_VitalsOK = 0x00000155,
        StringNames__Enum_VitalsDEAD = 0x00000156,
        StringNames__Enum_VitalsDC = 0x00000157,
        StringNames__Enum_ColorOrange = 0x00000158,
        StringNames__Enum_ColorBlue = 0x00000159,
        StringNames__Enum_ColorRed = 0x0000015a,
        StringNames__Enum_ColorBrown = 0x0000015b,
        StringNames__Enum_ColorGreen = 0x0000015c,
        StringNames__Enum_ColorPink = 0x0000015d,
        StringNames__Enum_ColorWhite = 0x0000015e,
        StringNames__Enum_ColorYellow = 0x0000015f,
        StringNames__Enum_ColorBlack = 0x00000160,
        StringNames__Enum_ColorPurple = 0x00000161,
        StringNames__Enum_ColorCyan = 0x00000162,
        StringNames__Enum_ColorLime = 0x00000163,
        StringNames__Enum_MedID = 0x00000164,
        StringNames__Enum_MedC = 0x00000165,
        StringNames__Enum_MedHT = 0x00000166,
        StringNames__Enum_MedBT = 0x00000167,
        StringNames__Enum_MedWT = 0x00000168,
        StringNames__Enum_MedETA = 0x00000169,
        StringNames__Enum_MedHello = 0x0000016a,
        StringNames__Enum_PetFailFetchData = 0x0000016b,
        StringNames__Enum_BadResult = 0x0000016c,
        StringNames__Enum_More = 0x0000016d,
        StringNames__Enum_Processing = 0x0000016e,
        StringNames__Enum_ExitGame = 0x0000016f,
        StringNames__Enum_WaitingForHost = 0x00000170,
        StringNames__Enum_LeftGameError = 0x00000171,
        StringNames__Enum_PlayerWasBannedBy = 0x00000172,
        StringNames__Enum_PlayerWasKickedBy = 0x00000173,
        StringNames__Enum_CamEast = 0x00000174,
        StringNames__Enum_CamCentral = 0x00000175,
        StringNames__Enum_CamNortheast = 0x00000176,
        StringNames__Enum_CamSouth = 0x00000177,
        StringNames__Enum_CamSouthwest = 0x00000178,
        StringNames__Enum_CamNorthwest = 0x00000179,
        StringNames__Enum_LoadingFailed = 0x0000017a,
        StringNames__Enum_LobbySizeWarning = 0x0000017b,
        StringNames__Enum_Okay = 0x0000017c,
        StringNames__Enum_OkayDontShow = 0x0000017d,
        StringNames__Enum_Nevermind = 0x0000017e,
        StringNames__Enum_Dummy = 0x0000017f,
        StringNames__Enum_Bad = 0x00000180,
        StringNames__Enum_Status = 0x00000181,
        StringNames__Enum_Fine = 0x00000182,
        StringNames__Enum_OK = 0x00000183,
        StringNames__Enum_PetTryOn = 0x00000184,
        StringNames__Enum_SecondsAbbv = 0x00000185,
        StringNames__Enum_SecurityLogsSystem = 0x00000186,
        StringNames__Enum_SecurityCamsSystem = 0x00000187,
        StringNames__Enum_AdminMapSystem = 0x00000188,
        StringNames__Enum_VitalsSystem = 0x00000189,
        StringNames__Enum_BanButton = 0x0000018a,
        StringNames__Enum_KickButton = 0x0000018b,
        StringNames__Enum_ReportButton = 0x0000018c,
        StringNames__Enum_ReportConfirmation = 0x0000018d,
        StringNames__Enum_ReportBadName = 0x0000018e,
        StringNames__Enum_ReportBadChat = 0x0000018f,
        StringNames__Enum_ReportHacking = 0x00000190,
        StringNames__Enum_ReportHarassment = 0x00000191,
        StringNames__Enum_ReportWhy = 0x00000192,
        StringNames__Enum_Visor = 0x00000193,
        StringNames__Enum_NamePlate = 0x00000194,
        StringNames__Enum_Visors = 0x00000195,
        StringNames__Enum_NamePlates = 0x00000196,
        StringNames__Enum_Cosmicube = 0x00000197,
        StringNames__Enum_Cosmicubes = 0x00000198,
        StringNames__Enum_Activate = 0x00000199,
        StringNames__Enum_Deactivate = 0x0000019a,
        StringNames__Enum_Owned = 0x0000019b,
        StringNames__Enum_Purchase = 0x0000019c,
        StringNames__Enum_CosmicubeProgression = 0x0000019d,
        StringNames__Enum_ViewCube = 0x0000019e,
        StringNames__Enum_ConfirmPurchaseHeader = 0x0000019f,
        StringNames__Enum_ConfirmPurchaseText = 0x000001a0,
        StringNames__Enum_DeactivateCube = 0x000001a1,
        StringNames__Enum_ActivateCube = 0x000001a2,
        StringNames__Enum_Bundles = 0x000001a3,
        StringNames__Enum_Stars = 0x000001a4,
        StringNames__Enum_PurchasingLabel = 0x000001a5,
        StringNames__Enum_MouseMovement = 0x000001a6,
        StringNames__Enum_KeyboardOptions = 0x000001a7,
        StringNames__Enum_RemapBindings = 0x000001a8,
        StringNames__Enum_KeyboardBindingsHeader = 0x000001a9,
        StringNames__Enum_PolishRuby = 0x000001f4,
        StringNames__Enum_ResetBreakers = 0x000001f5,
        StringNames__Enum_Decontaminate = 0x000001f6,
        StringNames__Enum_MakeBurger = 0x000001f7,
        StringNames__Enum_UnlockSafe = 0x000001f8,
        StringNames__Enum_SortRecords = 0x000001f9,
        StringNames__Enum_PutAwayPistols = 0x000001fa,
        StringNames__Enum_FixShower = 0x000001fb,
        StringNames__Enum_CleanToilet = 0x000001fc,
        StringNames__Enum_DressMannequin = 0x000001fd,
        StringNames__Enum_PickUpTowels = 0x000001fe,
        StringNames__Enum_RewindTapes = 0x000001ff,
        StringNames__Enum_StartFans = 0x00000200,
        StringNames__Enum_DevelopPhotos = 0x00000201,
        StringNames__Enum_GetBiggolSword = 0x00000202,
        StringNames__Enum_PutAwayRifles = 0x00000203,
        StringNames__Enum_StopCharles = 0x00000204,
        StringNames__Enum_AuthLeftOkay = 0x00000205,
        StringNames__Enum_AuthRightOkay = 0x00000206,
        StringNames__Enum_AuthLeftActive = 0x00000207,
        StringNames__Enum_AuthRightActive = 0x00000208,
        StringNames__Enum_AuthLeftNotActive = 0x00000209,
        StringNames__Enum_AuthRightNotActive = 0x0000020a,
        StringNames__Enum_VaultRoom = 0x00000226,
        StringNames__Enum_Cockpit = 0x00000227,
        StringNames__Enum_Armory = 0x00000228,
        StringNames__Enum_Kitchen = 0x00000229,
        StringNames__Enum_ViewingDeck = 0x0000022a,
        StringNames__Enum_HallOfPortraits = 0x0000022b,
        StringNames__Enum_Medical = 0x0000022c,
        StringNames__Enum_CargoBay = 0x0000022d,
        StringNames__Enum_Ventilation = 0x0000022e,
        StringNames__Enum_Showers = 0x0000022f,
        StringNames__Enum_Engine = 0x00000230,
        StringNames__Enum_Brig = 0x00000231,
        StringNames__Enum_MeetingRoom = 0x00000232,
        StringNames__Enum_Records = 0x00000233,
        StringNames__Enum_Lounge = 0x00000234,
        StringNames__Enum_GapRoom = 0x00000235,
        StringNames__Enum_MainHall = 0x00000236,
        StringNames__Enum_RevealCode = 0x00000237,
        StringNames__Enum_DirtyHeader = 0x00000238,
        StringNames__Enum_ErrorServerOverload = 0x000002bc,
        StringNames__Enum_ErrorIntentionalLeaving = 0x000002bd,
        StringNames__Enum_ErrorFocusLost = 0x000002be,
        StringNames__Enum_ErrorBanned = 0x000002bf,
        StringNames__Enum_ErrorKicked = 0x000002c0,
        StringNames__Enum_ErrorBannedNoCode = 0x000002c1,
        StringNames__Enum_ErrorKickedNoCode = 0x000002c2,
        StringNames__Enum_ErrorHacking = 0x000002c3,
        StringNames__Enum_ErrorFullGame = 0x000002c4,
        StringNames__Enum_ErrorStartedGame = 0x000002c5,
        StringNames__Enum_ErrorNotFoundGame = 0x000002c6,
        StringNames__Enum_ErrorInactivity = 0x000002c7,
        StringNames__Enum_ErrorGenericOnlineDisconnect = 0x000002c8,
        StringNames__Enum_ErrorGenericLocalDisconnect = 0x000002c9,
        StringNames__Enum_ErrorInvalidName = 0x000002ca,
        StringNames__Enum_ErrorUnknown = 0x000002cb,
        StringNames__Enum_ErrorIncorrectVersion = 0x000002cc,
        StringNames__Enum_ErrorNotAuthenticated = 0x000002cd,
        StringNames__Enum_ErrorInternalServer = 0x000002ce,
        StringNames__Enum_ErrorPlatformLock = 0x000002cf,
        StringNames__Enum_ErrorLobbyInactivity = 0x000002d0,
        StringNames__Enum_ErrorMatchmakerInactivity = 0x000002d1,
        StringNames__Enum_ErrorInvalidGameOptions = 0x000002d2,
        StringNames__Enum_ErrorNoServersAvailable = 0x000002d3,
        StringNames__Enum_ErrorQuickmatchDisabled = 0x000002d4,
        StringNames__Enum_ErrorTooManyGames = 0x000002d5,
        StringNames__Enum_ErrorDuplicateConnection = 0x000002d6,
        StringNames__Enum_ErrorTooManyRequests = 0x000002d7,
        StringNames__Enum_ErrorSanction = 0x000002d8,
        StringNames__Enum_VentDirection = 0x000003e8,
        StringNames__Enum_VentMove = 0x000003e9,
        StringNames__Enum_MenuNavigate = 0x000003ea,
        StringNames__Enum_NoTranslation = 0x000003eb,
        StringNames__Enum_NsoError = 0x000003ec,
        StringNames__Enum_RolesSettings = 0x000005dc,
        StringNames__Enum_ScientistRole = 0x000005dd,
        StringNames__Enum_EngineerRole = 0x000005de,
        StringNames__Enum_GuardianAngelRole = 0x000005df,
        StringNames__Enum_ShapeshifterRole = 0x000005e0,
        StringNames__Enum_ScientistBlurb = 0x000005e1,
        StringNames__Enum_EngineerBlurb = 0x000005e2,
        StringNames__Enum_GuardianAngelBlurb = 0x000005e3,
        StringNames__Enum_ShapeshifterBlurb = 0x000005e4,
        StringNames__Enum_CrewmateBlurb = 0x000005e5,
        StringNames__Enum_ImpostorBlurb = 0x000005e6,
        StringNames__Enum_YourRoleIs = 0x000005e7,
        StringNames__Enum_ShapeshiftAbility = 0x000005e8,
        StringNames__Enum_VentAbility = 0x000005e9,
        StringNames__Enum_VitalsAbility = 0x000005ea,
        StringNames__Enum_ProtectAbility = 0x000005eb,
        StringNames__Enum_ShapeshiftAbilityUndo = 0x000005ec,
        StringNames__Enum_RoleChanceAndQuantity = 0x000005ed,
        StringNames__Enum_ProtectedRecently = 0x000005ee,
        StringNames__Enum_ShapeshifterDuration = 0x000005ef,
        StringNames__Enum_ShapeshifterCooldown = 0x000005f0,
        StringNames__Enum_ShapeshifterLeaveSkin = 0x000005f1,
        StringNames__Enum_ScientistCooldown = 0x000005f2,
        StringNames__Enum_GuardianAngelCooldown = 0x000005f3,
        StringNames__Enum_EngineerCooldown = 0x000005f4,
        StringNames__Enum_ScientistBlurbMed = 0x000005f5,
        StringNames__Enum_ScientistBlurbLong = 0x000005f6,
        StringNames__Enum_EngineerBlurbMed = 0x000005f7,
        StringNames__Enum_EngineerBlurbLong = 0x000005f8,
        StringNames__Enum_GuardianAngelBlurbMed = 0x000005f9,
        StringNames__Enum_GuardianAngelBlurbLong = 0x000005fa,
        StringNames__Enum_ShapeshifterBlurbMed = 0x000005fb,
        StringNames__Enum_ShapeshifterBlurbLong = 0x000005fc,
        StringNames__Enum_RoleHint = 0x000005fd,
        StringNames__Enum_EngineerInVentCooldown = 0x000005fe,
        StringNames__Enum_ScientistBatteryCharge = 0x000005ff,
        StringNames__Enum_GuardianAngelDuration = 0x00000600,
        StringNames__Enum_GuardianAngelImpostorSeeProtect = 0x00000601,
        StringNames__Enum_StatsRoleWins = 0x00000602,
        StringNames__Enum_StatsEngineerVents = 0x00000603,
        StringNames__Enum_StatsScientistChargesGained = 0x00000604,
        StringNames__Enum_StatsGuardianAngelCrewmatesProtected = 0x00000605,
        StringNames__Enum_StatsShapeshifterShiftedKills = 0x00000606,
        StringNames__Enum_CrewmateGhostRole = 0x00000607,
        StringNames__Enum_ImpostorGhostRole = 0x00000608,
        StringNames__Enum_HauntAbilityName = 0x00000609,
        StringNames__Enum_SeekButton = 0x0000060a,
        StringNames__Enum_SanctionDuration = 0x000006a4,
        StringNames__Enum_SanctionPermanent = 0x000006a5,
        StringNames__Enum_SanctionConduct = 0x000006a6,
        StringNames__Enum_SanctionImpersonationCeleb = 0x000006a7,
        StringNames__Enum_SanctionSpamming = 0x000006a8,
        StringNames__Enum_SanctionInappropriateNameUnsportsmanlike = 0x000006a9,
        StringNames__Enum_SanctionUnsportsmanlikeConduct = 0x000006aa,
        StringNames__Enum_SanctionImpersonationDevelopers = 0x000006ab,
        StringNames__Enum_SanctionInappropriateChatPersonalInfo = 0x000006ac,
        StringNames__Enum_SanctionInappropriateNameDerogatory = 0x000006ad,
        StringNames__Enum_SanctionInappropriateNameNsfw = 0x000006ae,
        StringNames__Enum_SanctionBullying = 0x000006af,
        StringNames__Enum_SanctionCheatingHacking = 0x000006b0,
        StringNames__Enum_SanctionInappropriateChatDating = 0x000006b1,
        StringNames__Enum_SanctionWeaponizingRules = 0x000006b2,
        StringNames__Enum_SanctionRepeatOffender3 = 0x000006b3,
        StringNames__Enum_SanctionSexualMisconduct = 0x000006b4,
        StringNames__Enum_SanctionDoxing = 0x000006b5,
        StringNames__Enum_SanctionIllegalActivity = 0x000006b6,
        StringNames__Enum_SanctionHarassment = 0x000006b7,
        StringNames__Enum_SanctionSelfHarmPromotion = 0x000006b8,
        StringNames__Enum_SanctionRepeatOffender10 = 0x000006b9,
        StringNames__Enum_SanctionUnknown = 0x000006ba,
        StringNames__Enum_ScreenShakeOption = 0x0000076c,
        StringNames__Enum_FeaturedItems = 0x0000076d,
        StringNames__Enum_FeaturedBundles = 0x0000076e,
        StringNames__Enum_FeaturedCubes = 0x0000076f,
        StringNames__Enum_BugReportPopUpAttachScreenshotDesc = 0x00000770,
        StringNames__Enum_UserIdTokenError = 0x00000771,
        StringNames__Enum_NewGameMode = 0x00000772,
        StringNames__Enum_NewModeInfo = 0x00000773,
        StringNames__Enum_HideSeekHowToPlayTitleOne = 0x00000774,
        StringNames__Enum_HideSeekHowToPlayCaptionOne = 0x00000775,
        StringNames__Enum_HideSeekHowToPlayCaptionTwo = 0x00000776,
        StringNames__Enum_HideSeekHowToPlayCaptionThree = 0x00000777,
        StringNames__Enum_HideSeekHowToPlayPageOne = 0x00000778,
        StringNames__Enum_HideSeekHowToPlayImpostorOne = 0x00000779,
        StringNames__Enum_HideSeekHowToPlaySubtextOne = 0x0000077a,
        StringNames__Enum_HideSeekHowToPlayCrewmateInfoOne = 0x0000077b,
        StringNames__Enum_HideSeekHowToPlayCrewmateInfoTwo = 0x0000077c,
        StringNames__Enum_HideSeekHowToPlayImpostorInfoOne = 0x0000077d,
        StringNames__Enum_HideSeekHowToPlayFlashlightDefault = 0x0000077e,
        StringNames__Enum_HideSeekHowToPlayFinalHide = 0x0000077f,
        StringNames__Enum_HideSeekHowToPlayFlashlightMobile = 0x00000780,
        StringNames__Enum_HideSeekHowToPlayFlashlightSwitch = 0x00000781,
        StringNames__Enum_HideSeekHowToPlayFlashlightConsoles = 0x00000782,
        StringNames__Enum_HideSeekHowToPlayFlashlightPlayStation = 0x00000783,
        StringNames__Enum_QCLocationLaptop = 0x000007d0,
        StringNames__Enum_QCLocationSkeld = 0x000007d1,
        StringNames__Enum_QCLocationMira = 0x000007d2,
        StringNames__Enum_QCLocationPolus = 0x000007d3,
        StringNames__Enum_QCSystemsStart = 0x000007d4,
        StringNames__Enum_QCSystemsKick = 0x000007d5,
        StringNames__Enum_QCCrewI = 0x000007d6,
        StringNames__Enum_QCCrewMe = 0x000007d7,
        StringNames__Enum_QCCrewNoOne = 0x000007d8,
        StringNames__Enum_QCAccAKilledB = 0x000007d9,
        StringNames__Enum_QCAccAKilledBNeg = 0x000007da,
        StringNames__Enum_QCAccAIsSuspicious = 0x000007db,
        StringNames__Enum_QCAccAIsSuspiciousNeg = 0x000007dc,
        StringNames__Enum_QCAccASawBVent = 0x000007dd,
        StringNames__Enum_QCAccASawBVentNeg = 0x000007de,
        StringNames__Enum_QCAccAWasChasingB = 0x000007df,
        StringNames__Enum_QCAccAWasChasingBNeg = 0x000007e0,
        StringNames__Enum_QCAccAIsLying = 0x000007e1,
        StringNames__Enum_QCAccAIsLyingNeg = 0x000007e2,
        StringNames__Enum_QCAccVoteA = 0x000007e3,
        StringNames__Enum_QCAccVoteANeg = 0x000007e4,
        StringNames__Enum_QCAccADidntReport = 0x000007e5,
        StringNames__Enum_QCResYes = 0x000007e6,
        StringNames__Enum_QCResNo = 0x000007e7,
        StringNames__Enum_QCResDontKnow = 0x000007e8,
        StringNames__Enum_QCResDontKnowNeg = 0x000007e9,
        StringNames__Enum_QCResAWas = 0x000007ea,
        StringNames__Enum_QCResAWasNeg = 0x000007eb,
        StringNames__Enum_QCResADid = 0x000007ec,
        StringNames__Enum_QCResADidNeg = 0x000007ed,
        StringNames__Enum_QCResVote = 0x000007ee,
        StringNames__Enum_QCResVoteNeg = 0x000007ef,
        StringNames__Enum_QCResAWasAtB = 0x000007f0,
        StringNames__Enum_QCResAWasAtBNeg = 0x000007f1,
        StringNames__Enum_QCResRip = 0x000007f2,
        StringNames__Enum_QCResRipNeg = 0x000007f3,
        StringNames__Enum_QCResLies = 0x000007f4,
        StringNames__Enum_QCResLiesNeg = 0x000007f5,
        StringNames__Enum_QCQstWhere = 0x000007f6,
        StringNames__Enum_QCQstWho = 0x000007f7,
        StringNames__Enum_QCQstWhoWasWith = 0x000007f8,
        StringNames__Enum_QCQstWhatWasADoing = 0x000007f9,
        StringNames__Enum_QCQstWhoFixedA = 0x000007fa,
        StringNames__Enum_QCQstWhereWasA = 0x000007fb,
        StringNames__Enum_QCQstBodyOrMeeting = 0x000007fc,
        StringNames__Enum_QCStaASawB = 0x000007fd,
        StringNames__Enum_QCStaAWasWithB = 0x000007fe,
        StringNames__Enum_QCStaADidB = 0x000007ff,
        StringNames__Enum_QCStaASelfReported = 0x00000800,
        StringNames__Enum_QCStaDoubleKill = 0x00000801,
        StringNames__Enum_QCStaWasSelfReport = 0x00000802,
        StringNames__Enum_QCStaPleaseDoTasks = 0x00000803,
        StringNames__Enum_QCStaBodyWasInA = 0x00000804,
        StringNames__Enum_QCStaACalledMeeting = 0x00000805,
        StringNames__Enum_QCLocation = 0x00000806,
        StringNames__Enum_QCSystems = 0x00000807,
        StringNames__Enum_QCCrew = 0x00000808,
        StringNames__Enum_QCAccusation = 0x00000809,
        StringNames__Enum_QCResponse = 0x0000080a,
        StringNames__Enum_QCQuestion = 0x0000080b,
        StringNames__Enum_QCStatements = 0x0000080c,
        StringNames__Enum_ANY = 0x0000080d,
        StringNames__Enum_ChatType = 0x0000080e,
        StringNames__Enum_QuickChatOnly = 0x0000080f,
        StringNames__Enum_FreeChatOnly = 0x00000810,
        StringNames__Enum_FreeOrQuickChat = 0x00000811,
        StringNames__Enum_DateOfBirth = 0x00000812,
        StringNames__Enum_DateOfBirthEnter = 0x00000813,
        StringNames__Enum_Month = 0x00000814,
        StringNames__Enum_Day = 0x00000815,
        StringNames__Enum_Year = 0x00000816,
        StringNames__Enum_January = 0x00000817,
        StringNames__Enum_February = 0x00000818,
        StringNames__Enum_March = 0x00000819,
        StringNames__Enum_April = 0x0000081a,
        StringNames__Enum_May = 0x0000081b,
        StringNames__Enum_June = 0x0000081c,
        StringNames__Enum_July = 0x0000081d,
        StringNames__Enum_August = 0x0000081e,
        StringNames__Enum_September = 0x0000081f,
        StringNames__Enum_October = 0x00000820,
        StringNames__Enum_November = 0x00000821,
        StringNames__Enum_December = 0x00000822,
        StringNames__Enum_Submit = 0x00000823,
        StringNames__Enum_QCMore = 0x00000824,
        StringNames__Enum_Success = 0x00000825,
        StringNames__Enum_Failed = 0x00000826,
        StringNames__Enum_ErrorCreate = 0x00000827,
        StringNames__Enum_SuccessCreate = 0x00000828,
        StringNames__Enum_Close = 0x00000829,
        StringNames__Enum_ErrorLogIn = 0x0000082a,
        StringNames__Enum_SuccessLogIn = 0x0000082b,
        StringNames__Enum_AccountInfo = 0x0000082c,
        StringNames__Enum_Account = 0x0000082d,
        StringNames__Enum_UserName = 0x0000082e,
        StringNames__Enum_Height = 0x0000082f,
        StringNames__Enum_Weight = 0x00000830,
        StringNames__Enum_SignIn = 0x00000831,
        StringNames__Enum_CreateAccount = 0x00000832,
        StringNames__Enum_RequestPermission = 0x00000833,
        StringNames__Enum_RandomizeName = 0x00000834,
        StringNames__Enum_AccountLinking = 0x00000835,
        StringNames__Enum_ChangeName = 0x00000836,
        StringNames__Enum_LogOut = 0x00000837,
        StringNames__Enum_GuardianWait = 0x00000838,
        StringNames__Enum_EmailEdit = 0x00000839,
        StringNames__Enum_EmailResend = 0x0000083a,
        StringNames__Enum_GuestContinue = 0x0000083b,
        StringNames__Enum_GuardianEmailSent = 0x0000083c,
        StringNames__Enum_GuardianCheckEmail = 0x0000083d,
        StringNames__Enum_EditName = 0x0000083e,
        StringNames__Enum_Name = 0x0000083f,
        StringNames__Enum_CreateAccountQuestion = 0x00000840,
        StringNames__Enum_DoYouWantCreate = 0x00000841,
        StringNames__Enum_PermissionRequired = 0x00000842,
        StringNames__Enum_NeedPermissionText = 0x00000843,
        StringNames__Enum_GuardianEmailTitle = 0x00000844,
        StringNames__Enum_Send = 0x00000845,
        StringNames__Enum_NewEmail = 0x00000846,
        StringNames__Enum_ConfirmEmail = 0x00000847,
        StringNames__Enum_EditEmail = 0x00000848,
        StringNames__Enum_Loading = 0x00000849,
        StringNames__Enum_Welcome = 0x0000084a,
        StringNames__Enum_DLLNotFoundAccountError = 0x0000084b,
        StringNames__Enum_ContinueOffline = 0x0000084c,
        StringNames__Enum_CreateTryAgain = 0x0000084d,
        StringNames__Enum_WantToLogIn = 0x0000084e,
        StringNames__Enum_GoOffline = 0x0000084f,
        StringNames__Enum_PlayAsGuest = 0x00000850,
        StringNames__Enum_LogInTitle = 0x00000851,
        StringNames__Enum_LogInInfoText = 0x00000852,
        StringNames__Enum_ShowAccountSupportID5 = 0x00000853,
        StringNames__Enum_ShowAccountSupportID4 = 0x00000854,
        StringNames__Enum_ShowAccountSupportID3 = 0x00000855,
        StringNames__Enum_ShowAccountSupportID2 = 0x00000856,
        StringNames__Enum_ShowAccountSupportID1 = 0x00000857,
        StringNames__Enum_YouAreNotOnline = 0x00000858,
        StringNames__Enum_SaveGameOutOfSpaceMessage = 0x00000859,
        StringNames__Enum_SaveGameOutOfSpaceConfirm = 0x0000085a,
        StringNames__Enum_SaveGameOutOfSpaceCancel = 0x0000085b,
        StringNames__Enum_EngagementScreen = 0x0000085c,
        StringNames__Enum_EngagementScreenSignIn = 0x0000085d,
        StringNames__Enum_FollowUs = 0x0000085e,
        StringNames__Enum_ColorMaroon = 0x0000085f,
        StringNames__Enum_ColorRose = 0x00000860,
        StringNames__Enum_ColorBanana = 0x00000861,
        StringNames__Enum_ColorGray = 0x00000862,
        StringNames__Enum_ColorTan = 0x00000863,
        StringNames__Enum_ColorSunset = 0x00000864,
        StringNames__Enum_QuickChatInstructionsStart = 0x00000865,
        StringNames__Enum_QuickChatInstructionsChild = 0x00000866,
        StringNames__Enum_QuickChatInstructionsGuest = 0x00000867,
        StringNames__Enum_QuickChatInstructionsFull = 0x00000868,
        StringNames__Enum_SwitchEShopBrowseAll = 0x00000869,
        StringNames__Enum_ColorCoral = 0x0000086a,
        StringNames__Enum_GuardianEmail = 0x0000086b,
        StringNames__Enum_LocalButton = 0x0000086c,
        StringNames__Enum_OnlineButton = 0x0000086d,
        StringNames__Enum_HowToPlayButton = 0x0000086e,
        StringNames__Enum_FreePlayButton = 0x0000086f,
        StringNames__Enum_PublicHeader = 0x00000870,
        StringNames__Enum_PrivateHeader = 0x00000871,
        StringNames__Enum_HostHeader = 0x00000872,
        StringNames__Enum_EmergencyMeeting = 0x00000873,
        StringNames__Enum_BodyReported = 0x00000874,
        StringNames__Enum_PlayAgain = 0x00000875,
        StringNames__Enum_QuitLabel = 0x00000876,
        StringNames__Enum_DownloadLabel = 0x00000877,
        StringNames__Enum_UploadLabel = 0x00000878,
        StringNames__Enum_TimeRemaining = 0x00000879,
        StringNames__Enum_AnnouncementLabel = 0x0000087a,
        StringNames__Enum_StartLabel = 0x0000087b,
        StringNames__Enum_UseLabel = 0x0000087c,
        StringNames__Enum_KillLabel = 0x0000087d,
        StringNames__Enum_SabotageLabel = 0x0000087e,
        StringNames__Enum_VentLabel = 0x0000087f,
        StringNames__Enum_OptionsLabel = 0x00000880,
        StringNames__Enum_ReportLabel = 0x00000881,
        StringNames__Enum_CO2Label = 0x00000882,
        StringNames__Enum_NutriLabel = 0x00000883,
        StringNames__Enum_RADLabel = 0x00000884,
        StringNames__Enum_WaterLabel = 0x00000885,
        StringNames__Enum_DiscussLabel = 0x00000886,
        StringNames__Enum_DeadLabel = 0x00000887,
        StringNames__Enum_SkippedVoting = 0x00000888,
        StringNames__Enum_ProceedLabel = 0x00000889,
        StringNames__Enum_HolidayHatLabel = 0x0000088a,
        StringNames__Enum_HatLabel = 0x0000088b,
        StringNames__Enum_PetLabel = 0x0000088c,
        StringNames__Enum_SkinLabel = 0x0000088d,
        StringNames__Enum_DoorlogLabel = 0x0000088e,
        StringNames__Enum_VitalsLabel = 0x0000088f,
        StringNames__Enum_InsufficientStorageError = 0x00000890,
        StringNames__Enum_NetworkError = 0x00000891,
        StringNames__Enum_OtherDownloadError = 0x00000892,
        StringNames__Enum_DownloadingLabel = 0x00000893,
        StringNames__Enum_DownloadSizeLabel = 0x00000894,
        StringNames__Enum_SkipVoteLabel = 0x00000895,
        StringNames__Enum_LogInInfoTextSwitch = 0x00000896,
        StringNames__Enum_WeatherDataDownload = 0x00000897,
        StringNames__Enum_BeginLabel = 0x00000898,
        StringNames__Enum_QuietLabel = 0x00000899,
        StringNames__Enum_LogLabel = 0x0000089a,
        StringNames__Enum_ReadingLabel = 0x0000089b,
        StringNames__Enum_UploadingLabel = 0x0000089c,
        StringNames__Enum_ConnectionLabel = 0x0000089d,
        StringNames__Enum_GoodLabel = 0x0000089e,
        StringNames__Enum_PoorLabel = 0x0000089f,
        StringNames__Enum_NoneLabel = 0x000008a0,
        StringNames__Enum_ProgressLabel = 0x000008a1,
        StringNames__Enum_PerfectLabel = 0x000008a2,
        StringNames__Enum_NoDeadBodiesFound = 0x000008a3,
        StringNames__Enum_AirshipBundle = 0x000008a4,
        StringNames__Enum_PolusBundle = 0x000008a5,
        StringNames__Enum_PolusSkinBundle = 0x000008a6,
        StringNames__Enum_MiraBundle = 0x000008a7,
        StringNames__Enum_MiraSkinBundle = 0x000008a8,
        StringNames__Enum_PetAlien2 = 0x000008a9,
        StringNames__Enum_PetAlien1 = 0x000008aa,
        StringNames__Enum_PetAnimal = 0x000008ab,
        StringNames__Enum_PetCrewmate = 0x000008ac,
        StringNames__Enum_PetStickmin = 0x000008ad,
        StringNames__Enum_PrisonerSkin = 0x000008ae,
        StringNames__Enum_Cyborg_RHM = 0x000008af,
        StringNames__Enum_CCC_Officer = 0x000008b0,
        StringNames__Enum_VentCleaning = 0x000008b1,
        StringNames__Enum_CleanUp = 0x000008b2,
        StringNames__Enum_ControllerDisconnectedMessage = 0x000008b3,
        StringNames__Enum_TermsOfUseTitle = 0x000008b4,
        StringNames__Enum_PPAndToUTitle = 0x000008b5,
        StringNames__Enum_ComePlayDiscord = 0x000008b6,
        StringNames__Enum_SupportEmail = 0x000008b7,
        StringNames__Enum_SupportIDLabel = 0x000008b8,
        StringNames__Enum_pk05_davehat = 0x000008b9,
        StringNames__Enum_pk05_Ellie = 0x000008ba,
        StringNames__Enum_pk05_Svenhat = 0x000008bb,
        StringNames__Enum_pk05_Burthat = 0x000008bc,
        StringNames__Enum_pk05_Ellryhat = 0x000008bd,
        StringNames__Enum_pk05_monocles = 0x000008be,
        StringNames__Enum_pk05_cheesetoppat = 0x000008bf,
        StringNames__Enum_pk05_Macbethhat = 0x000008c0,
        StringNames__Enum_pk05_HenryToppat = 0x000008c1,
        StringNames__Enum_pk05_EllieToppat = 0x000008c2,
        StringNames__Enum_pk05_GeoffreyToppat = 0x000008c3,
        StringNames__Enum_InviteFriends = 0x000008c4,
        StringNames__Enum_Continue = 0x000008c5,
        StringNames__Enum_GameComplete = 0x000008c6,
        StringNames__Enum_XpGained = 0x000008c7,
        StringNames__Enum_PodsEarned = 0x000008c8,
        StringNames__Enum_CosmicubeNodeUnlocked = 0x000008c9,
        StringNames__Enum_LevelShorthand = 0x000008ca,
        StringNames__Enum_PrestigeLevelShorthand = 0x000008cb,
        StringNames__Enum_MaxLevel = 0x000008cc,
        StringNames__Enum_EquipLabel = 0x000008cd,
        StringNames__Enum_XpGainedValue = 0x000008ce,
        StringNames__Enum_PSNErrorSessionFailed = 0x000008cf,
        StringNames__Enum_PSNErrorSessionJoinFailed = 0x000008d0,
        StringNames__Enum_PSNErrorSessionGetInfoFailed = 0x000008d1,
        StringNames__Enum_PSNErrorPSNConnectionLost = 0x000008d2,
        StringNames__Enum_PSNErrorUserSignedOut = 0x000008d3,
        StringNames__Enum_CrossPlayTitle = 0x000008d4,
        StringNames__Enum_CrossPlayAllPlatforms = 0x000008d5,
        StringNames__Enum_CrossPlaySamePlatform = 0x000008d6,
        StringNames__Enum_QuickChat = 0x000008d7,
        StringNames__Enum_TimeOutText = 0x000008d8,
        StringNames__Enum_RetryText = 0x000008d9,
        StringNames__Enum_PlayerLevel = 0x000008da,
        StringNames__Enum_PlayerXp = 0x000008db,
        StringNames__Enum_PlayerLevelExtremeShorthand = 0x000008dc,
        StringNames__Enum_Max = 0x000008dd,
        StringNames__Enum_Wardrobe = 0x000008de,
        StringNames__Enum_CopiedText = 0x000008df,
        StringNames__Enum_LinkAccount = 0x000008e0,
        StringNames__Enum_CreateNewAccount = 0x000008e1,
        StringNames__Enum_LinkExistingAccount = 0x000008e2,
        StringNames__Enum_LinkAccountExplanation = 0x000008e3,
        StringNames__Enum_LinkAccountCode = 0x000008e4,
        StringNames__Enum_ErrorLink = 0x000008e5,
        StringNames__Enum_UnlinkAccount = 0x000008e6,
        StringNames__Enum_ConfirmUnlinkAccount = 0x000008e7,
        StringNames__Enum_UnlinkAccountExplain = 0x000008e8,
        StringNames__Enum_UnlinkAccountExplainConfirm = 0x000008e9,
        StringNames__Enum_UnlinkError = 0x000008ea,
        StringNames__Enum_UnlinkSuccess = 0x000008eb,
        StringNames__Enum_ConfirmLinkExistingAccount = 0x000008ec,
        StringNames__Enum_LinkExistingAccountExplain = 0x000008ed,
        StringNames__Enum_LinkExistingAccountExplainConfirm = 0x000008ee,
        StringNames__Enum_ResetAccount = 0x000008ef,
        StringNames__Enum_CrossPlayEnabledWarning = 0x000008f0,
        StringNames__Enum_StoreComingSoon = 0x000008f1,
        StringNames__Enum_Locked = 0x000008f2,
        StringNames__Enum_FailPurchase = 0x000008f3,
        StringNames__Enum_FailPurchaseUnknown = 0x000008f4,
        StringNames__Enum_FailPurchaseAlreadyOwn = 0x000008f5,
        StringNames__Enum_FailPurchaseCurrency = 0x000008f6,
        StringNames__Enum_FailPurchaseCubeOwn = 0x000008f7,
        StringNames__Enum_ErrorPlatformParentalControlsBlock = 0x000008f8,
        StringNames__Enum_Crewmates = 0x000008f9,
        StringNames__Enum_Colors = 0x000008fa,
        StringNames__Enum_Active = 0x000008fb,
        StringNames__Enum_Equipped = 0x000008fc,
        StringNames__Enum_QCLocationAirship = 0x000008fd,
        StringNames__Enum_XboxShopBrowseAll = 0x000008fe,
        StringNames__Enum_PSShopBrowseAll = 0x000008ff,
        StringNames__Enum_SteamNotInitialized = 0x00000900,
        StringNames__Enum_LoggedInErrorStarPurchase = 0x00000901,
        StringNames__Enum_StarDisclaimer = 0x00000902,
        StringNames__Enum_HowToPlayText_Consoles = 0x00000903,
        StringNames__Enum_ErrorQuickChatMode = 0x00000904,
        StringNames__Enum_ErrorLobbyUsersBlocked = 0x00000905,
        StringNames__Enum_ItchNoStars = 0x00000906,
        StringNames__Enum_CheckingPurchasesLabel = 0x00000907,
        StringNames__Enum_RedeemPurchasedItemsTitle = 0x00000908,
        StringNames__Enum_RedeemPurcahsedItemsExplain = 0x00000909,
        StringNames__Enum_RedeemProceed = 0x0000090a,
        StringNames__Enum_RedeemNotYet = 0x0000090b,
        StringNames__Enum_AccountIDDisplay = 0x0000090c,
        StringNames__Enum_RedeemNever = 0x0000090d,
        StringNames__Enum_AvailableFor = 0x0000090e,
        StringNames__Enum_GuestProgressionWarning = 0x0000090f,
        StringNames__Enum_ErrorSelfPlatformLock = 0x00000910,
        StringNames__Enum_ErrorCrossPlat = 0x00000911,
        StringNames__Enum_SettingsStreamerMode = 0x00000912,
        StringNames__Enum_RoomCodeInfo = 0x00000913,
        StringNames__Enum_AbbreviatedDay = 0x00000914,
        StringNames__Enum_AbbreviatedHour = 0x00000915,
        StringNames__Enum_AbbreviatedMinute = 0x00000916,
        StringNames__Enum_AbbreviatedSecond = 0x00000917,
        StringNames__Enum_MaxVentUses = 0x00000a8c,
        StringNames__Enum_MaxTimeInVent = 0x00000a8d,
        StringNames__Enum_MinCrewmatesForVitals = 0x00000a8e,
        StringNames__Enum_EscapeTime = 0x00000a8f,
        StringNames__Enum_AllTasksComplete = 0x00000a90,
        StringNames__Enum_EscapePrompt = 0x00000a91,
        StringNames__Enum_CrewmateFlashlightSize = 0x00000a92,
        StringNames__Enum_ImpostorFlashlightSize = 0x00000a93,
        StringNames__Enum_CrewmateLeadTime = 0x00000a94,
        StringNames__Enum_CrewmadeHideBlurb = 0x00000a95,
        StringNames__Enum_ImpostorKillBlurb = 0x00000a96,
        StringNames__Enum_HideCountdown = 0x00000a97,
        StringNames__Enum_ScaryMusicDistance = 0x00000a98,
        StringNames__Enum_ShortTaskTimeValue = 0x00000a99,
        StringNames__Enum_LongTaskTimeValue = 0x00000a9a,
        StringNames__Enum_CommonTaskTimeValue = 0x00000a9b,
        StringNames__Enum_UseFlashlight = 0x00000a9c,
        StringNames__Enum_FinalEscapeTime = 0x00000a9d,
        StringNames__Enum_VeryScaryMusicDistance = 0x00000a9e,
        StringNames__Enum_SeekerFinalSpeed = 0x00000a9f,
        StringNames__Enum_SeekerFinalVents = 0x00000aa0,
        StringNames__Enum_SeekerFinalMap = 0x00000aa1,
        StringNames__Enum_CrewmateVentCooldown = 0x00000aa2,
        StringNames__Enum_SeekerPings = 0x00000aa3,
        StringNames__Enum_MaxPingTime = 0x00000aa4,
        StringNames__Enum_ShowPingTime = 0x00000aa5,
        StringNames__Enum_MinPingTime = 0x00000aa6,
        StringNames__Enum_ShowCrewmateNames = 0x00000aa7,
        StringNames__Enum_ShowImpostorNames = 0x00000aa8,
        StringNames__Enum_HideActionButton = 0x00000aa9,
        StringNames__Enum_RuleOneCrewmates = 0x00000aaa,
        StringNames__Enum_RuleTwoCrewmates = 0x00000aab,
        StringNames__Enum_RuleThreeCrewmates = 0x00000aac,
        StringNames__Enum_RuleOneImpostor = 0x00000aad,
        StringNames__Enum_RuleTwoImpostor = 0x00000aae,
        StringNames__Enum_RuleThreeImpostor = 0x00000aaf,
        StringNames__Enum_RuleOneCrewmatesTitle = 0x00000ab0,
        StringNames__Enum_RuleTwoCrewmatesTitle = 0x00000ab1,
        StringNames__Enum_RuleThreeCrewmatesTitle = 0x00000ab2,
        StringNames__Enum_RuleOneImpostorTitle = 0x00000ab3,
        StringNames__Enum_RuleTwoImpostorTitle = 0x00000ab4,
        StringNames__Enum_RoundRobin = 0x00000ab5,
        StringNames__Enum_OptionUnavailablePublicLobby = 0x00000ab6,
        StringNames__Enum_StatsHidenSeekGamesCrewmateSurvived = 0x00000ab7,
        StringNames__Enum_StatsHidenSeekTimesVented = 0x00000ab8,
        StringNames__Enum_StatsTimesPettedPet = 0x00000ab9,
        StringNames__Enum_StatsImpostorKills_HideAndSeek = 0x00000aba,
        StringNames__Enum_StatsFastestCrewmateWin_HideAndSeek = 0x00000abb,
        StringNames__Enum_StatsFastestImpostorWin_HideAndSeek = 0x00000abc,
        StringNames__Enum_StatsHideAndSeekImpostorVictory = 0x00000abd,
        StringNames__Enum_StatsHideAndSeekCrewmateVictory = 0x00000abe,
        StringNames__Enum_AmongUsFriends = 0x00000af0,
        StringNames__Enum_FriendsGuestWarning = 0x00000af1,
        StringNames__Enum_PlatformFriends = 0x00000af2,
        StringNames__Enum_BlockedPlayers = 0x00000af3,
        StringNames__Enum_RecentPlayers = 0x00000af4,
        StringNames__Enum_LobbyLabel = 0x00000af5,
        StringNames__Enum_FriendCodeExplanation = 0x00000af6,
        StringNames__Enum_FriendCodeSuccess = 0x00000af7,
        StringNames__Enum_FriendRequestReceived = 0x00000af8,
        StringNames__Enum_FriendRequestSent = 0x00000af9,
        StringNames__Enum_GameLobbyInviteSent = 0x00000afa,
        StringNames__Enum_GameLobbyInviteReceived = 0x00000afb,
        StringNames__Enum_BlockPlayerConfirm = 0x00000afc,
        StringNames__Enum_RemoveFriendConfirm = 0x00000afd,
        StringNames__Enum_InviteToLobbyConfirm = 0x00000afe,
        StringNames__Enum_FriendCodeLabel = 0x00000aff,
        StringNames__Enum_FriendCodeCreationTitle = 0x00000b00,
        StringNames__Enum_FriendRequestSentFailed = 0x00000b01,
        StringNames__Enum_ErrorBadUsername = 0x00000b02,
        StringNames__Enum_ErrorUserNotFound = 0x00000b03,
        StringNames__Enum_ErrorThisIsYou = 0x00000b04,
        StringNames__Enum_ErrorFriendRequestExists = 0x00000b05,
        StringNames__Enum_ErrorAlreadyFriends = 0x00000b06,
        StringNames__Enum_GameLobbyInviteSentFailed = 0x00000b07,
        StringNames__Enum_BlockedPlayerFailed = 0x00000b08,
        StringNames__Enum_BlockedPlayer = 0x00000b09,
        StringNames__Enum_AlreadyBlocked = 0x00000b0a,
        StringNames__Enum_FriendList = 0x00000b0b,
        StringNames__Enum_NoNewRequests = 0x00000b0c,
        StringNames__Enum_AddFriendPrompt = 0x00000b0d,
        StringNames__Enum_NewRequests = 0x00000b0e,
        StringNames__Enum_Requests = 0x00000b0f,
        StringNames__Enum_AddFriend = 0x00000b10,
        StringNames__Enum_StreamWarning = 0x00000b11,
        StringNames__Enum_FriendsListPermissionsWarning = 0x00000b12,
        StringNames__Enum_AddFriendConfirm = 0x00000b13,
        StringNames__Enum_UnfriendConfirm = 0x00000b14,
        StringNames__Enum_UnblockConfirm = 0x00000b15,
        StringNames__Enum_SettingsEnableFriendInvites = 0x00000b16,
        StringNames__Enum_ErrorCrossPlatformCommunication = 0x00000b17,
        StringNames__Enum_ErrorPlatformFriends = 0x00000b18,
        StringNames__Enum_ErrorPlayerBlockedYou = 0x00000b19,
        StringNames__Enum_ErrorRecipientMaxFriendRequests = 0x00000b1a,
        StringNames__Enum_ErrorSenderMaxFriendRequests = 0x00000b1b,
        StringNames__Enum_ErrorMaxFriends = 0x00000b1c,
        StringNames__Enum_ErrorRecipientMaxFriends = 0x00000b1d,
        StringNames__Enum_ParentPortalButton = 0x00000b1e,
        StringNames__Enum_FriendsListEmailSent = 0x00000b1f,
        StringNames__Enum_AndroidAssetBundleWarning = 0x00000b20,
        StringNames__Enum_FreeChatLinkWarning = 0x00000b21,
        StringNames__Enum_FriendListUnavailable = 0x00000b22,
        StringNames__Enum_SignInIssueTitle = 0x00000b23,
        StringNames__Enum_SignInIssueText = 0x00000b24,
        StringNames__Enum_Ghost = 0x00000b25,
        StringNames__Enum_CurrentlyHaunting = 0x00000b26,
        StringNames__Enum_RestorePurchases = 0x00000b27,
        StringNames__Enum_QCAccIsRole = 0x00000bb8,
        StringNames__Enum_QCAccIsRoleNeg = 0x00000bb9,
        StringNames__Enum_QCAccShapeshited = 0x00000bba,
        StringNames__Enum_QCStaShapeshifterSkin = 0x00000bbb,
        StringNames__Enum_QCResIsBeingFramed = 0x00000bbc,
        StringNames__Enum_QCResIsRoleMaybe = 0x00000bbd,
        StringNames__Enum_QCResCloseTo = 0x00000bbe,
        StringNames__Enum_QCResProtected = 0x00000bbf,
        StringNames__Enum_QCRoles = 0x00000bc0,
        StringNames__Enum_ErrorFailedToCreateGame = 0x00000bc1,
        StringNames__Enum_ErrorFailedToJoinCreatedGame = 0x00000bc2,
        StringNames__Enum_ErrorDisconnectBeforeJoining = 0x00000bc3,
        StringNames__Enum_ErrorDisconnectPacket = 0x00000bc4,
        StringNames__Enum_PSEULA_SIEA = 0x00000bc5,
        StringNames__Enum_PSEULA_SIEE = 0x00000bc6,
        StringNames__Enum_ShowAccountID = 0x00000bc7,
        StringNames__Enum_HideAccountID = 0x00000bc8,
        StringNames__Enum_HiddenAccountID = 0x00000bc9,
        StringNames__Enum_ErrorLobbyFailedGettingBlockedUsers = 0x00000bca,
        StringNames__Enum_SteamOverlayDisabled = 0x00000bcb,
        StringNames__Enum_QCOnlyInfo = 0x00000bcc,
        StringNames__Enum_FreeChatInfo = 0x00000bcd,
        StringNames__Enum_FreeChatWarning = 0x00000bce,
        StringNames__Enum_TryAgain = 0x00000bcf,
        StringNames__Enum_TempDisabled = 0x00000bd0,
        StringNames__Enum_TempDisabledLinkExplain = 0x00000bd1,
        StringNames__Enum_RedeemPopup = 0x00000bd2,
        StringNames__Enum_RedeemButton = 0x00000bd3,
        StringNames__Enum_Decontamination3 = 0x00000bd4,
        StringNames__Enum_MergeGuestAccountText = 0x00000bd5,
        StringNames__Enum_MergeGuestAccountTitle = 0x00000bd6,
        StringNames__Enum_ErrorCommunications = 0x00000bd7,
        StringNames__Enum_ManageAccountTitle = 0x00000bd8,
        StringNames__Enum_ManageAccountText = 0x00000bd9,
        StringNames__Enum_Email = 0x00000bda,
        StringNames__Enum_BugReportPopUpSubmittedText = 0x00000bdb,
        StringNames__Enum_BugReportPopUpCategoryLabel = 0x00000bdc,
        StringNames__Enum_BugReportPopUpDescriptionLabel = 0x00000bdd,
        StringNames__Enum_BugReportPopUpTitle = 0x00000bde,
        StringNames__Enum_BugReportCategoryServerIssues = 0x00000bdf,
        StringNames__Enum_BugReportCategoryGameplayIssue = 0x00000be0,
        StringNames__Enum_BugReportCategoryAccountManagement = 0x00000be1,
        StringNames__Enum_BugReportCategoryBilling = 0x00000be2,
        StringNames__Enum_BugReportCategoryGeneral = 0x00000be3,
        StringNames__Enum_BugReportIssueButton = 0x00000be4,
        StringNames__Enum_BugReportPopUpSubmissionFailedText = 0x00000be5,
        StringNames__Enum_BugReportPopUpAttachScreenshotLabel = 0x00000be6,
        StringNames__Enum_SettingsColorblind = 0x00000c80,
        StringNames__Enum_SettingsHelp = 0x00000c81,
        StringNames__Enum_SecLogEntryColorblind = 0x00000c82,
        StringNames__Enum_DeleteAccount = 0x00000c83,
        StringNames__Enum_DoNotDeleteAccount = 0x00000c84,
        StringNames__Enum_AccountDeleteHelp = 0x00000c85,
        StringNames__Enum_AccountUnDeleteHelp = 0x00000c86,
        StringNames__Enum_ConfirmDelete = 0x00000c87,
        StringNames__Enum_ConfirmDeleteAccounts = 0x00000c88,
        StringNames__Enum_ConfirmDeleteAccountsEmpty = 0x00000c89,
        StringNames__Enum_AccountRequestDelete = 0x00000c8a,
        StringNames__Enum_HasBeenKilled = 0x00000c8b,
        StringNames__Enum_GameType = 0x00000dac,
        StringNames__Enum_GameTypeError = 0x00000dad,
        StringNames__Enum_GameTypeClassic = 0x00000dae,
        StringNames__Enum_GameTypeHideAndSeek = 0x00000daf,
        StringNames__Enum_PetAction = 0x00000db0,
        StringNames__Enum_CreateLabel = 0x00000db1,
        StringNames__Enum_TagFiltersTitle = 0x00000db2,
        StringNames__Enum_TagFiltersHelpFindGame = 0x00000db3,
        StringNames__Enum_TagFiltersHelpCreate = 0x00000db4,
        StringNames__Enum_TagsFilteredSingular = 0x00000db5,
        StringNames__Enum_TagsFilteredPlural = 0x00000db6,
        StringNames__Enum_TagsAppliedSingular = 0x00000db7,
        StringNames__Enum_TagsAppliedPlural = 0x00000db8,
        StringNames__Enum_DefaultFilterTag_FirstTime = 0x00000db9,
        StringNames__Enum_DefaultFilterTag_Casual = 0x00000dba,
        StringNames__Enum_DefaultFilterTag_Serious = 0x00000dbb,
        StringNames__Enum_DefaultFilterTag_Expert = 0x00000dbc,
    };

#endif

#pragma endregion

#pragma region SwitchSystem
    struct __declspec(align(4)) SwitchSystem__Fields
    {
        float DetoriorationTime;
        uint8_t Value;
        float timer;
        uint8_t ExpectedSwitches;
        uint8_t ActualSwitches;
        bool _IsDirty_k__BackingField;
    };

    struct SwitchSystem
    {
        struct SwitchSystem__Class* klass;
        void* monitor;
        struct SwitchSystem__Fields fields;
    };

    struct SwitchSystem__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData Detoriorate;
        VirtualInvokeData RepairDamage;
        VirtualInvokeData UpdateSystem;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData get_IsActive;
    };

    struct SwitchSystem__StaticFields
    {
    };

    struct SwitchSystem__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SwitchSystem__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SwitchSystem__VTable vtable;
    };
#pragma endregion

#pragma region ISystemType
    struct ISystemType
    {
        struct ISystemType__Class* klass;
        void* monitor;
    };
    struct ISystemType__VTable
    {
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData Detoriorate;
        VirtualInvokeData RepairDamage;
        VirtualInvokeData UpdateSystem;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct ISystemType__StaticFields
    {
    };

    struct ISystemType__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ISystemType__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ISystemType__VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType_
    struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType_
    {
        int32_t hashCode;
        int32_t next;
#if defined(_CPLUSPLUS_)
        SystemTypes__Enum key;
#else
        uint8_t key;
#endif
        struct ISystemType* value;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array
    struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array
    {
        struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__Class* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType_ vector[32];
    };
    struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__VTable
    {
    };

    struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__StaticFields
    {
    };

    struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array__VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType_
    struct __declspec(align(4)) Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___Fields
    {
        struct Dictionary_2_SystemTypes_ISystemType_* dictionary;
    };

    struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType_
    {
        struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___Class* klass;
        void* monitor;
        struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___Fields fields;
    };
    struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_TKey__get_IsReadOnly;
        VirtualInvokeData System_Collections_Generic_ICollection_TKey__Add;
        VirtualInvokeData System_Collections_Generic_ICollection_TKey__Clear;
        VirtualInvokeData System_Collections_Generic_ICollection_TKey__Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData System_Collections_Generic_ICollection_TKey__Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_TKey__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Count_2;
    };

    struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___StaticFields
    {
    };

    struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType___VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType_
    struct __declspec(align(4)) Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___Fields
    {
        struct Dictionary_2_SystemTypes_ISystemType_* dictionary;
    };

    struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType_
    {
        struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___Class* klass;
        void* monitor;
        struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___Fields fields;
    };
    struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_TValue__get_IsReadOnly;
        VirtualInvokeData System_Collections_Generic_ICollection_TValue__Add;
        VirtualInvokeData System_Collections_Generic_ICollection_TValue__Clear;
        VirtualInvokeData System_Collections_Generic_ICollection_TValue__Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData System_Collections_Generic_ICollection_TValue__Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_TValue__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Count_2;
    };

    struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___StaticFields
    {
    };

    struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType___VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_SystemTypes_ISystemType_
    struct __declspec(align(4)) Dictionary_2_SystemTypes_ISystemType___Fields
    {
        struct Int32__Array* buckets;
        struct Dictionary_2_TKey_TValue_Entry_SystemTypes_ISystemType___Array* entries;
        int32_t count;
        int32_t version;
        int32_t freeList;
        int32_t freeCount;
        void* comparer;
        struct Dictionary_2_TKey_TValue_KeyCollection_SystemTypes_ISystemType_* keys;
        struct Dictionary_2_TKey_TValue_ValueCollection_SystemTypes_ISystemType_* values;
        struct Object* _syncRoot;
    };

    struct Dictionary_2_SystemTypes_ISystemType_
    {
        struct Dictionary_2_SystemTypes_ISystemType___Class* klass;
        MonitorData* monitor;
        struct Dictionary_2_SystemTypes_ISystemType___Fields fields;
    };
    struct Dictionary_2_SystemTypes_ISystemType___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Values;
        VirtualInvokeData ContainsKey;
        VirtualInvokeData Add;
        VirtualInvokeData Remove;
        VirtualInvokeData TryGetValue;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___get_IsReadOnly;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Add;
        VirtualInvokeData Clear;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Contains;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___CopyTo;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_System_Collections_Generic_KeyValuePair_TKey_TValue___GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IDictionary_get_Item;
        VirtualInvokeData System_Collections_IDictionary_set_Item;
        VirtualInvokeData System_Collections_IDictionary_get_Keys;
        VirtualInvokeData System_Collections_IDictionary_get_Values;
        VirtualInvokeData System_Collections_IDictionary_Contains;
        VirtualInvokeData System_Collections_IDictionary_Add;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IDictionary_get_IsReadOnly;
        VirtualInvokeData System_Collections_IDictionary_get_IsFixedSize;
        VirtualInvokeData System_Collections_IDictionary_GetEnumerator;
        VirtualInvokeData System_Collections_IDictionary_Remove;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData ContainsKey_1;
        VirtualInvokeData TryGetValue_1;
        VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Values;
        VirtualInvokeData get_Count_2;
        VirtualInvokeData GetObjectData;
        VirtualInvokeData OnDeserialization;
        VirtualInvokeData GetObjectData_1;
        VirtualInvokeData OnDeserialization_1;
    };

    struct System_Collections_Generic_Dictionary_TKey__TValue__RGCTXs {
        MethodInfo* _0_System_Collections_Generic_Dictionary_TKey__TValue___ctor;
        MethodInfo* _1_System_Collections_Generic_Dictionary_TKey__TValue__Initialize;
        MethodInfo* _2_System_Collections_Generic_EqualityComparer_TKey__get_Default;
        Il2CppClass* _3_System_Collections_Generic_EqualityComparer_TKey_;
        MethodInfo* _4_System_Collections_Generic_Dictionary_TKey__TValue___ctor;
        Il2CppClass* _5_System_Collections_Generic_ICollection_KeyValuePair_TKey__TValue__;
        Il2CppType* _6_System_Collections_Generic_Dictionary_TKey__TValue_;
        Il2CppClass* _7_System_Collections_Generic_Dictionary_TKey__TValue_;
        MethodInfo* _8_System_Collections_Generic_Dictionary_TKey__TValue__Add;
        Il2CppClass* _9_System_Collections_Generic_IEnumerable_KeyValuePair_TKey__TValue__;
        Il2CppClass* _10_System_Collections_Generic_IEnumerator_KeyValuePair_TKey__TValue__;
        MethodInfo* _11_System_Collections_Generic_KeyValuePair_TKey__TValue__get_Key;
        MethodInfo* _12_System_Collections_Generic_KeyValuePair_TKey__TValue__get_Value;
        Il2CppClass* _13_System_Collections_Generic_Dictionary_KeyCollection_TKey__TValue_;
        MethodInfo* _14_System_Collections_Generic_Dictionary_KeyCollection_TKey__TValue___ctor;
        Il2CppClass* _15_System_Collections_Generic_Dictionary_ValueCollection_TKey__TValue_;
        MethodInfo* _16_System_Collections_Generic_Dictionary_ValueCollection_TKey__TValue___ctor;
        MethodInfo* _17_System_Collections_Generic_Dictionary_TKey__TValue__FindEntry;
        MethodInfo* _18_System_Collections_Generic_Dictionary_TKey__TValue__TryInsert;
        MethodInfo* _19_System_Collections_Generic_EqualityComparer_TValue__get_Default;
        Il2CppClass* _20_System_Collections_Generic_EqualityComparer_TValue_;
        MethodInfo* _21_System_Collections_Generic_EqualityComparer_TValue__Equals;
        MethodInfo* _22_System_Collections_Generic_Dictionary_TKey__TValue__Remove;
        Il2CppClass* _23_TValue;
        MethodInfo* _24_System_Collections_Generic_Dictionary_TKey__TValue__get_Count;
        Il2CppClass* _25_System_Collections_Generic_KeyValuePair_TKey__TValue_;
        MethodInfo* _26_System_Collections_Generic_KeyValuePair_TKey__TValue___ctor;
        Il2CppClass* _27_System_Collections_Generic_Dictionary_Enumerator_TKey__TValue_;
        MethodInfo* _28_System_Collections_Generic_Dictionary_Enumerator_TKey__TValue___ctor;
        Il2CppType* _29_System_Collections_Generic_IEqualityComparer_TKey_;
        Il2CppClass* _30_System_Collections_Generic_KeyValuePair_TKey__TValue___;
        MethodInfo* _31_System_Collections_Generic_Dictionary_TKey__TValue__CopyTo;
        Il2CppType* _32_System_Collections_Generic_KeyValuePair_TKey__TValue___;
        Il2CppClass* _33_TKey;
        Il2CppClass* _34_System_Collections_Generic_IEqualityComparer_TKey_;
        Il2CppClass* _35_System_Collections_Generic_Dictionary_Entry_TKey__TValue___;
        MethodInfo* _36_System_Collections_Generic_Dictionary_TKey__TValue__Resize;
        MethodInfo* _37_System_Collections_Generic_Dictionary_TKey__TValue__Resize;
        Il2CppClass* _38_System_Collections_Generic_KeyValuePair_TKey__TValue___;
        MethodInfo* _39_System_Collections_Generic_Dictionary_TKey__TValue__get_Keys;
        MethodInfo* _40_System_Collections_Generic_Dictionary_TKey__TValue__get_Values;
        MethodInfo* _41_System_Collections_Generic_Dictionary_TKey__TValue__IsCompatibleKey;
        Il2CppClass* _42_System_Collections_Generic_Dictionary_TKey__TValue_;
        MethodInfo* _43_System_Collections_Generic_Dictionary_TKey__TValue__set_Item;
        Il2CppType* _44_TValue;
        Il2CppType* _45_TKey;
        MethodInfo* _46_System_Collections_Generic_Dictionary_TKey__TValue__ContainsKey;
    };

    struct Dictionary_2_SystemTypes_ISystemType___StaticFields
    {
    };

    struct Dictionary_2_SystemTypes_ISystemType___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_SystemTypes_ISystemType___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_SystemTypes_ISystemType___VTable vtable;
    };
#pragma endregion

#pragma region AirshipStatus
    struct AirshipStatus__Fields {
        struct ShipStatus__Fields _;
        void* Ladders;
        void* SpawnInGame;
        struct MovingPlatformBehaviour* GapPlatform;
        void* ShowerParticles;
        void* LightAffectors;
        struct GameObject* outOfOrderPlat;
    };

    struct AirshipStatus
    {
        struct AirshipStatus__Class* klass;
        void* monitor;
        struct AirshipStatus__Fields fields;
    };

    struct AirshipStatus__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData OnEnable;
        VirtualInvokeData RepairGameOverSystems;
        VirtualInvokeData Start;
        VirtualInvokeData SpawnPlayer;
        VirtualInvokeData OnMeetingCalled;
        VirtualInvokeData PrespawnStep;
        VirtualInvokeData CalculateLightRadius;
    };

    struct AirshipStatus__StaticFields
    {
    };

    struct AirshipStatus__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct AirshipStatus__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct AirshipStatus__VTable vtable;
    };
#pragma endregion

#pragma region GameData_PlayerOutfit
    struct __declspec(align(4)) GameData_PlayerOutfit__Fields {
        bool dontCensorName;
        int32_t ColorId;
        struct String* HatId;
        struct String* PetId;
        struct String* SkinId;
        struct String* VisorId;
        struct String* NamePlateId;
        struct String* preCensorName;
        struct String* postCensorName;
    };

    struct GameData_PlayerOutfit {
        struct GameData_PlayerOutfit__Class* klass;
        MonitorData* monitor;
        struct GameData_PlayerOutfit__Fields fields;
    };

    struct GameData_PlayerOutfit__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct GameData_PlayerOutfit__StaticFields
    {
    };

    struct GameData_PlayerOutfit__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct GameData_PlayerOutfit__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct GameData_PlayerOutfit__VTable vtable;
    };
#pragma endregion

#pragma region Int32__Array
    struct Int32__Array
    {
        struct Int32__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        int32_t vector[32];
    };
    struct Int32__Array__VTable
    {
    };

    struct Int32__Array__StaticFields
    {
    };

    struct Int32__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Int32__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Int32__Array__VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit_
    struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit_
    {
        int32_t hashCode;
        int32_t next;
#if defined(_CPLUSPLUS_)
        PlayerOutfitType__Enum key;
#else
        int32_t key;
#endif
        struct GameData_PlayerOutfit* value;
    };
#pragma endregion

#pragma region Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array
    struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array
    {
        struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__Class* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit_ vector[32];
    };
    struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__VTable
    {
    };

    struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__StaticFields
    {
    };

    struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array__VTable vtable;
    };
#pragma endregion

#pragma region Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit_
    struct __declspec(align(4)) Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___Fields
    {
        struct Int32__Array* buckets;
        struct Dictionary_2_TKey_TValue_Entry_PlayerOutfitType_GameData_PlayerOutfit___Array* entries;
        int32_t count;
        int32_t version;
        int32_t freeList;
        int32_t freeCount;
        struct IEqualityComparer_1_PlayerOutfitType_* comparer;
        struct Dictionary_2_TKey_TValue_KeyCollection_PlayerOutfitType_GameData_PlayerOutfit_* keys;
        struct Dictionary_2_TKey_TValue_ValueCollection_PlayerOutfitType_GameData_PlayerOutfit_* values;
        struct Object* _syncRoot;
    };

    struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit_
    {
        struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___Class* klass;
        MonitorData* monitor;
        struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___Fields fields;
    };
    struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Values;
        VirtualInvokeData ContainsKey;
        VirtualInvokeData Add;
        VirtualInvokeData Remove;
        VirtualInvokeData TryGetValue;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___get_IsReadOnly;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Add;
        VirtualInvokeData Clear;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Contains;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___CopyTo;
        VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_System_Collections_Generic_KeyValuePair_TKey_TValue___GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IDictionary_get_Item;
        VirtualInvokeData System_Collections_IDictionary_set_Item;
        VirtualInvokeData System_Collections_IDictionary_get_Keys;
        VirtualInvokeData System_Collections_IDictionary_get_Values;
        VirtualInvokeData System_Collections_IDictionary_Contains;
        VirtualInvokeData System_Collections_IDictionary_Add;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IDictionary_get_IsReadOnly;
        VirtualInvokeData System_Collections_IDictionary_get_IsFixedSize;
        VirtualInvokeData System_Collections_IDictionary_GetEnumerator;
        VirtualInvokeData System_Collections_IDictionary_Remove;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData ContainsKey_1;
        VirtualInvokeData TryGetValue_1;
        VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Values;
        VirtualInvokeData get_Count_2;
        VirtualInvokeData GetObjectData;
        VirtualInvokeData OnDeserialization;
        VirtualInvokeData GetObjectData_1;
        VirtualInvokeData OnDeserialization_1;
    };

    struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___StaticFields
    {
    };

    struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit___VTable vtable;
    };
#pragma endregion

#pragma region RoleTypes__Enum
#if defined(_CPLUSPLUS_)
    enum class RoleTypes__Enum : uint16_t {
        Crewmate = 0x0000,
        Impostor = 0x0001,
        Scientist = 0x0002,
        Engineer = 0x0003,
        GuardianAngel = 0x0004,
        Shapeshifter = 0x0005,
        CrewmateGhost = 0x0006,
        ImpostorGhost = 0x0007,
    };

#else
    enum RoleTypes__Enum {
        RoleTypes__Enum_Crewmate = 0x0000,
        RoleTypes__Enum_Impostor = 0x0001,
        RoleTypes__Enum_Scientist = 0x0002,
        RoleTypes__Enum_Engineer = 0x0003,
        RoleTypes__Enum_GuardianAngel = 0x0004,
        RoleTypes__Enum_Shapeshifter = 0x0005,
        RoleTypes__Enum_CrewmateGhost = 0x0006,
        RoleTypes__Enum_ImpostorGhost = 0x0007,
    };

#endif
#pragma endregion

#pragma region RoleTeamTypes__Enum
#if defined(_CPLUSPLUS_)
    enum class RoleTeamTypes__Enum : int32_t
    {
        Crewmate = 0x00000000,
        Impostor = 0x00000001,
    };

#else
    enum RoleTeamTypes__Enum
    {
        RoleTeamTypes__Enum_Crewmate = 0x00000000,
        RoleTeamTypes__Enum_Impostor = 0x00000001,
    };

#endif
#pragma endregion

#pragma region QuickChatModes__Enum
#if defined(_CPLUSPLUS_)
    enum class QuickChatModes__Enum : int32_t
    {
        FreeChatOrQuickChat = 0x00000001,
        QuickChatOnly = 0x00000002,
    };

#else
    enum QuickChatModes__Enum
    {
        QuickChatModes__Enum_FreeChatOrQuickChat = 0x00000001,
        QuickChatModes__Enum_QuickChatOnly = 0x00000002,
    };

#endif
#pragma endregion

#pragma region RoleBehaviour
    struct RoleBehaviour__Fields {
        struct MonoBehaviour__Fields _;
#if defined(_CPLUSPLUS_)
        RoleTypes__Enum Role;
#else
        uint16_t Role;
#endif
#if defined(_CPLUSPLUS_)
        StringNames__Enum StringName;
#else
        int32_t StringName;
#endif
#if defined(_CPLUSPLUS_)
        StringNames__Enum BlurbName;
#else
        int32_t BlurbName;
#endif
#if defined(_CPLUSPLUS_)
        StringNames__Enum BlurbNameMed;
#else
        int32_t BlurbNameMed;
#endif
#if defined(_CPLUSPLUS_)
        StringNames__Enum BlurbNameLong;
#else
        int32_t BlurbNameLong;
#endif
        struct Color NameColor;
        bool TasksCountTowardProgress;
        bool CanUseKillButton;
        bool CanBeKilled;
        bool CanVent;
        bool AffectedByLightAffectors;
        int32_t MaxCount;
#if defined(_CPLUSPLUS_)
        RoleTeamTypes__Enum TeamType;
#else
        int32_t TeamType;
#endif
        struct AbilityButtonSettings* Ability;
#if defined(_CPLUSPLUS_)
        RoleTypes__Enum DefaultGhostRole;
#else
        uint16_t DefaultGhostRole;
#endif
        struct AudioClip* UseSound;
        struct AudioClip* IntroSound;
        struct PlayerControl* Player;
        void* buttonManager;
    };

    struct RoleBehaviour
    {
        struct RoleBehaviour__Class* klass;
        MonitorData* monitor;
        struct RoleBehaviour__Fields fields;
    };

    struct RoleBehaviour__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData __unknown;
        VirtualInvokeData get_IsAffectedByComms;
        VirtualInvokeData CanUse;
        VirtualInvokeData DidWin;
        VirtualInvokeData Deinitialize;
        VirtualInvokeData SpawnTaskHeader;
        VirtualInvokeData UseAbility;
        VirtualInvokeData OnMeetingStart;
        VirtualInvokeData OnVotingComplete;
        VirtualInvokeData Initialize;
        VirtualInvokeData SetUsableTarget;
        VirtualInvokeData SetPlayerTarget;
        VirtualInvokeData SetCooldown;
        VirtualInvokeData IsValidTarget;
        VirtualInvokeData FindClosestTarget;
        VirtualInvokeData GetAbilityDistance;
        VirtualInvokeData AdjustTasks;
        VirtualInvokeData AppendTaskHint;
    };

    struct RoleBehaviour__StaticFields {
        struct List_1_PlayerControl_* tempPlayerList;
    };

    struct RoleBehaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct RoleBehaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct RoleBehaviour__VTable vtable;
    };
#pragma endregion

#pragma region Nullable_1_AmongUs_GameOptions_RoleTypes_
    struct Nullable_1_AmongUs_GameOptions_RoleTypes_
    {
#if defined(_CPLUSPLUS_)
        RoleTypes__Enum value;
#else
        uint16_t value;
#endif
        bool has_value;
    };
#pragma endregion

#pragma region GameData_PlayerInfo
    struct __declspec(align(4)) GameData_PlayerInfo__Fields {
        uint8_t PlayerId;
        struct String* FriendCode;
        struct String* Puid;
#if defined(_CPLUSPLUS_)
        RoleTypes__Enum RoleType;
#else
        uint16_t RoleType;
#endif
        struct Nullable_1_AmongUs_GameOptions_RoleTypes_ RoleWhenAlive;
        struct Dictionary_2_PlayerOutfitType_GameData_PlayerOutfit_* Outfits;
        uint32_t PlayerLevel;
        bool Disconnected;
        struct RoleBehaviour* Role;
        void* Tasks;
        bool IsDead;
        struct PlayerControl* _object;
    };

    struct GameData_PlayerInfo
    {
        struct GameData_PlayerInfo__Class* klass;
        void* monitor;
        struct GameData_PlayerInfo__Fields fields;
    };

    struct GameData_PlayerInfo__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct GameData_PlayerInfo__StaticFields
    {
    };

    struct GameData_PlayerInfo__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct GameData_PlayerInfo__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct GameData_PlayerInfo__VTable vtable;
    };
#pragma endregion

#pragma region MovingPlatformBehaviour
    struct MovingPlatformBehaviour__Fields {
        struct MonoBehaviour__Fields _;
        struct Vector3 LeftPosition;
        struct Vector3 RightPosition;
        struct Vector3 DisabledPosition;
        struct Vector3 LeftUsePosition;
        struct Vector3 RightUsePosition;
        void* MovingSound;
        bool IsLeft;
        struct PlayerControl* Target;
        uint8_t useId;
        bool _IsDirty_k__BackingField;
    };

    struct MovingPlatformBehaviour
    {
        struct MovingPlatformBehaviour__Class* klass;
        void* monitor;
        struct MovingPlatformBehaviour__Fields fields;
    };

    struct MovingPlatformBehaviour__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData Detoriorate;
        VirtualInvokeData RepairDamage;
        VirtualInvokeData UpdateSystem;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct MovingPlatformBehaviour__StaticFields
    {
    };

    struct MovingPlatformBehaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MovingPlatformBehaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MovingPlatformBehaviour__VTable vtable;
    };
#pragma endregion

#pragma region Minigame

#if defined(_CPLUSPLUS_)
    enum class TransitionType__Enum : int32_t
    {
        SlideBottom = 0x00000000,
        Alpha = 0x00000001,
        None = 0x00000002,
    };

#else
    enum TransitionType__Enum
    {
        TransitionType__Enum_SlideBottom = 0x00000000,
        TransitionType__Enum_Alpha = 0x00000001,
        TransitionType__Enum_None = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class Minigame_CloseState__Enum : int32_t
    {
        None = 0x00000000,
        Waiting = 0x00000001,
        Closing = 0x00000002,
    };

#else
    enum Minigame_CloseState__Enum
    {
        Minigame_CloseState__Enum_None = 0x00000000,
        Minigame_CloseState__Enum_Waiting = 0x00000001,
        Minigame_CloseState__Enum_Closing = 0x00000002,
    };

#endif

    struct Minigame__Fields {
        struct MonoBehaviour__Fields _;
#if defined(_CPLUSPLUS_)
        TransitionType__Enum TransType;
#else
        int32_t TransType;
#endif
        struct Vector2 TargetPosition;
        void* MyTask;
        void* MyNormTask;
        void* _Console_k__BackingField;
#if defined(_CPLUSPLUS_)
        Minigame_CloseState__Enum amClosing;
#else
        int32_t amClosing;
#endif
        bool amOpening;
        void* OpenSound;
        void* CloseSound;
        void* inputHandler;
        void* logger;
    };

    struct Minigame
    {
        struct Minigame__Class* klass;
        void* monitor;
        struct Minigame__Fields fields;
    };

    struct Minigame__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Begin;
        VirtualInvokeData Close;
        VirtualInvokeData CoAnimateOpen;
        VirtualInvokeData CoDestroySelf;
    };

    struct Minigame__StaticFields
    {
        struct Minigame* Instance;
    };

    struct Minigame__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Minigame__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Minigame__VTable vtable;
    };
#pragma endregion

#pragma region DoorCardSwipeGame

#if defined(_CPLUSPLUS_)
    enum class DoorCardSwipeGame_TaskStages__Enum : int32_t
    {
        Before = 0x00000000,
        Animating = 0x00000001,
        Inserted = 0x00000002,
        After = 0x00000003,
    };

#else
    enum DoorCardSwipeGame_TaskStages__Enum
    {
        DoorCardSwipeGame_TaskStages__Enum_Before = 0x00000000,
        DoorCardSwipeGame_TaskStages__Enum_Animating = 0x00000001,
        DoorCardSwipeGame_TaskStages__Enum_Inserted = 0x00000002,
        DoorCardSwipeGame_TaskStages__Enum_After = 0x00000003,
    };

#endif

    struct DoorCardSwipeGame__Fields
    {
        struct Minigame__Fields _;
        struct Color gray;
        struct Color green;
#if defined(_CPLUSPLUS_)
        DoorCardSwipeGame_TaskStages__Enum State;
#else
        int32_t State;
#endif
        void* myController;
        void* YRange;
        float minAcceptedTime;
        struct Collider2D* col;
        struct SpriteRenderer* confirmSymbol;
        void* AcceptSymbol;
        void* RejectSymbol;
        struct TextMeshPro* StatusText;
        void* AcceptSound;
        void* DenySound;
        void* CardMove;
        void* WalletOut;
        float dragTime;
        bool moving;
        struct Vector2 prevStickInput;
        bool hadPrev;
        struct PlainDoor* MyDoor;
    };

    struct DoorCardSwipeGame
    {
        struct DoorCardSwipeGame__Class* klass;
        void* monitor;
        struct DoorCardSwipeGame__Fields fields;
    };

    struct DoorCardSwipeGame__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Begin;
        VirtualInvokeData Close;
        VirtualInvokeData CoAnimateOpen;
        VirtualInvokeData CoDestroySelf;
        VirtualInvokeData SetDoor;
    };

    struct DoorCardSwipeGame__StaticFields
    {
    };

    struct DoorCardSwipeGame__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct DoorCardSwipeGame__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct DoorCardSwipeGame__VTable vtable;
    };
#pragma endregion

#pragma region PlayerTask

#if defined(_CPLUSPLUS_)
    enum class TaskTypes__Enum : int32_t
    {
        SubmitScan = 0x00000000,
        PrimeShields = 0x00000001,
        FuelEngines = 0x00000002,
        ChartCourse = 0x00000003,
        StartReactor = 0x00000004,
        SwipeCard = 0x00000005,
        ClearAsteroids = 0x00000006,
        UploadData = 0x00000007,
        InspectSample = 0x00000008,
        EmptyChute = 0x00000009,
        EmptyGarbage = 0x0000000a,
        AlignEngineOutput = 0x0000000b,
        FixWiring = 0x0000000c,
        CalibrateDistributor = 0x0000000d,
        DivertPower = 0x0000000e,
        UnlockManifolds = 0x0000000f,
        ResetReactor = 0x00000010,
        FixLights = 0x00000011,
        CleanO2Filter = 0x00000012,
        FixComms = 0x00000013,
        RestoreOxy = 0x00000014,
        StabilizeSteering = 0x00000015,
        AssembleArtifact = 0x00000016,
        SortSamples = 0x00000017,
        MeasureWeather = 0x00000018,
        EnterIdCode = 0x00000019,
        BuyBeverage = 0x0000001a,
        ProcessData = 0x0000001b,
        RunDiagnostics = 0x0000001c,
        WaterPlants = 0x0000001d,
        MonitorOxygen = 0x0000001e,
        StoreArtifacts = 0x0000001f,
        FillCanisters = 0x00000020,
        ActivateWeatherNodes = 0x00000021,
        InsertKeys = 0x00000022,
        ResetSeismic = 0x00000023,
        ScanBoardingPass = 0x00000024,
        OpenWaterways = 0x00000025,
        ReplaceWaterJug = 0x00000026,
        RepairDrill = 0x00000027,
        AlignTelescope = 0x00000028,
        RecordTemperature = 0x00000029,
        RebootWifi = 0x0000002a,
        PolishRuby = 0x0000002b,
        ResetBreakers = 0x0000002c,
        Decontaminate = 0x0000002d,
        MakeBurger = 0x0000002e,
        UnlockSafe = 0x0000002f,
        SortRecords = 0x00000030,
        PutAwayPistols = 0x00000031,
        FixShower = 0x00000032,
        CleanToilet = 0x00000033,
        DressMannequin = 0x00000034,
        PickUpTowels = 0x00000035,
        RewindTapes = 0x00000036,
        StartFans = 0x00000037,
        DevelopPhotos = 0x00000038,
        GetBiggolSword = 0x00000039,
        PutAwayRifles = 0x0000003a,
        StopCharles = 0x0000003b,
        VentCleaning = 0x0000003c,
        None = 0x0000003d,
    };

#else
    enum TaskTypes__Enum
    {
        TaskTypes__Enum_SubmitScan = 0x00000000,
        TaskTypes__Enum_PrimeShields = 0x00000001,
        TaskTypes__Enum_FuelEngines = 0x00000002,
        TaskTypes__Enum_ChartCourse = 0x00000003,
        TaskTypes__Enum_StartReactor = 0x00000004,
        TaskTypes__Enum_SwipeCard = 0x00000005,
        TaskTypes__Enum_ClearAsteroids = 0x00000006,
        TaskTypes__Enum_UploadData = 0x00000007,
        TaskTypes__Enum_InspectSample = 0x00000008,
        TaskTypes__Enum_EmptyChute = 0x00000009,
        TaskTypes__Enum_EmptyGarbage = 0x0000000a,
        TaskTypes__Enum_AlignEngineOutput = 0x0000000b,
        TaskTypes__Enum_FixWiring = 0x0000000c,
        TaskTypes__Enum_CalibrateDistributor = 0x0000000d,
        TaskTypes__Enum_DivertPower = 0x0000000e,
        TaskTypes__Enum_UnlockManifolds = 0x0000000f,
        TaskTypes__Enum_ResetReactor = 0x00000010,
        TaskTypes__Enum_FixLights = 0x00000011,
        TaskTypes__Enum_CleanO2Filter = 0x00000012,
        TaskTypes__Enum_FixComms = 0x00000013,
        TaskTypes__Enum_RestoreOxy = 0x00000014,
        TaskTypes__Enum_StabilizeSteering = 0x00000015,
        TaskTypes__Enum_AssembleArtifact = 0x00000016,
        TaskTypes__Enum_SortSamples = 0x00000017,
        TaskTypes__Enum_MeasureWeather = 0x00000018,
        TaskTypes__Enum_EnterIdCode = 0x00000019,
        TaskTypes__Enum_BuyBeverage = 0x0000001a,
        TaskTypes__Enum_ProcessData = 0x0000001b,
        TaskTypes__Enum_RunDiagnostics = 0x0000001c,
        TaskTypes__Enum_WaterPlants = 0x0000001d,
        TaskTypes__Enum_MonitorOxygen = 0x0000001e,
        TaskTypes__Enum_StoreArtifacts = 0x0000001f,
        TaskTypes__Enum_FillCanisters = 0x00000020,
        TaskTypes__Enum_ActivateWeatherNodes = 0x00000021,
        TaskTypes__Enum_InsertKeys = 0x00000022,
        TaskTypes__Enum_ResetSeismic = 0x00000023,
        TaskTypes__Enum_ScanBoardingPass = 0x00000024,
        TaskTypes__Enum_OpenWaterways = 0x00000025,
        TaskTypes__Enum_ReplaceWaterJug = 0x00000026,
        TaskTypes__Enum_RepairDrill = 0x00000027,
        TaskTypes__Enum_AlignTelescope = 0x00000028,
        TaskTypes__Enum_RecordTemperature = 0x00000029,
        TaskTypes__Enum_RebootWifi = 0x0000002a,
        TaskTypes__Enum_PolishRuby = 0x0000002b,
        TaskTypes__Enum_ResetBreakers = 0x0000002c,
        TaskTypes__Enum_Decontaminate = 0x0000002d,
        TaskTypes__Enum_MakeBurger = 0x0000002e,
        TaskTypes__Enum_UnlockSafe = 0x0000002f,
        TaskTypes__Enum_SortRecords = 0x00000030,
        TaskTypes__Enum_PutAwayPistols = 0x00000031,
        TaskTypes__Enum_FixShower = 0x00000032,
        TaskTypes__Enum_CleanToilet = 0x00000033,
        TaskTypes__Enum_DressMannequin = 0x00000034,
        TaskTypes__Enum_PickUpTowels = 0x00000035,
        TaskTypes__Enum_RewindTapes = 0x00000036,
        TaskTypes__Enum_StartFans = 0x00000037,
        TaskTypes__Enum_DevelopPhotos = 0x00000038,
        TaskTypes__Enum_GetBiggolSword = 0x00000039,
        TaskTypes__Enum_PutAwayRifles = 0x0000003a,
        TaskTypes__Enum_StopCharles = 0x0000003b,
        TaskTypes__Enum_VentCleaning = 0x0000003c,
        TaskTypes__Enum_None = 0x0000003d,
    };

#endif

    struct PlayerTask__Fields
    {
        struct MonoBehaviour__Fields _;
        int32_t _Index_k__BackingField;
        uint32_t _Id_k__BackingField;
        struct PlayerControl* _Owner_k__BackingField;
#if defined(_CPLUSPLUS_)
        SystemTypes__Enum StartAt;
#else
        uint8_t StartAt;
#endif
#if defined(_CPLUSPLUS_)
        TaskTypes__Enum TaskType;
#else
        int32_t TaskType;
#endif
        void* MinigamePrefab;
        bool HasLocation;
        bool LocationDirty;
    };

    struct PlayerTask
    {
        struct PlayerTask__Class* klass;
        void* monitor;
        struct PlayerTask__Fields fields;
    };

    struct PlayerTask__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData __unknown;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData OnRemove;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData GetMinigamePrefab;
    };

    struct PlayerTask__StaticFields
    {
    };

    struct PlayerTask__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerTask__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerTask__VTable vtable;
    };
#pragma endregion

#pragma region PlayerTask__Array
    struct PlayerTask__Array
    {
        struct PlayerTask__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlayerTask* vector[32];
    };
    struct PlayerTask__Array__VTable
    {
    };

    struct PlayerTask__Array__StaticFields
    {
    };

    struct PlayerTask__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerTask__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerTask__Array__VTable vtable;
    };
#pragma endregion

#pragma region List_1_RoleEffectAnimation_
    struct __declspec(align(4)) List_1_RoleEffectAnimation___Fields {
        struct RoleEffectAnimation__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_RoleEffectAnimation_ {
        void* klass;
        MonitorData* monitor;
        struct List_1_RoleEffectAnimation___Fields fields;
    };

#if defined(_CPLUSPLUS_)
    enum class RoleEffectAnimation_EffectType__Enum : int32_t {
        Default = 0x00000000,
        ProtectLoop = 0x00000001,
        Shapeshift = 0x00000002,
    };

#else
    enum RoleEffectAnimation_EffectType__Enum {
        RoleEffectAnimation_EffectType__Enum_Default = 0x00000000,
        RoleEffectAnimation_EffectType__Enum_ProtectLoop = 0x00000001,
        RoleEffectAnimation_EffectType__Enum_Shapeshift = 0x00000002,
    };

#endif
#pragma endregion

#pragma region RoleEffectAnimation
    struct RoleEffectAnimation__Fields {
        struct MonoBehaviour__Fields _;
#if defined(_CPLUSPLUS_)
        RoleEffectAnimation_EffectType__Enum effectType;
#else
        int32_t effectType;
#endif
        struct AnimationClip* Clip;
        struct SpriteAnim* Animator;
        struct Action* MidAnimCB;
        struct SpriteRenderer* Renderer;
        struct AudioClip* UseSound;
        struct AudioSource* AudioSource;
        struct PlayerControl* parent;
    };

    struct RoleEffectAnimation {
        void* klass;
        MonitorData* monitor;
        struct RoleEffectAnimation__Fields fields;
    };

    struct RoleEffectAnimation__Array {
        void* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct RoleEffectAnimation* vector[32];
    };
#pragma endregion

#pragma region List_1_PlayerTask_
    struct __declspec(align(4)) List_1_PlayerTask___Fields
    {
        struct PlayerTask__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_PlayerTask_
    {
        struct List_1_PlayerTask___Class* klass;
        void* monitor;
        struct List_1_PlayerTask___Fields fields;
    };
    struct List_1_PlayerTask___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_PlayerTask___StaticFields
    {
        struct PlayerTask__Array* _emptyArray;
    };

    struct List_1_PlayerTask___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_PlayerTask___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_PlayerTask___VTable vtable;
    };
#pragma endregion

#pragma region VersionShower
    struct VersionShower__Fields
    {
        struct MonoBehaviour__Fields _;
        struct TextMeshPro* text;
    };

    struct VersionShower
    {
        struct VersionShower__Class* klass;
        void* monitor;
        struct VersionShower__Fields fields;
    };

    struct VersionShower__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct VersionShower__StaticFields
    {
    };

    struct VersionShower__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct VersionShower__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct VersionShower__VTable vtable;
    };
#pragma endregion

#pragma region FollowerCamera
    struct FollowerCamera__Fields {
        struct MonoBehaviour__Fields _;
        struct MonoBehaviour* Target;
        struct Vector2 Offset;
        bool Locked;
        float shakeAmount;
        float shakePeriod;
        struct Vector2 centerPosition;
    };

    struct FollowerCamera
    {
        struct FollowerCamera__Class* klass;
        void* monitor;
        struct FollowerCamera__Fields fields;
    };

    struct FollowerCamera__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct FollowerCamera__StaticFields
    {
    };

    struct FollowerCamera__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct FollowerCamera__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct FollowerCamera__VTable vtable;
    };
#pragma endregion

#pragma region GameData
    struct GameData__Fields
    {
        struct InnerNetObject__Fields _;
        struct List_1_GameData_PlayerInfo_* AllPlayers;
        int32_t TotalTasks;
        int32_t CompletedTasks;
        struct RoleBehaviour* DefaultRole;
    };

    struct GameData
    {
        void* klass;
        void* monitor;
        struct GameData__Fields fields;
    };

    struct GameData__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData HandleDisconnect;
        VirtualInvokeData HandleDisconnect_1;
    };

    struct GameData__StaticFields
    {
        struct GameData* Instance;
        void* randy;
    };

    struct GameData__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct GameData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct GameData__VTable vtable;
    };
#pragma endregion

#pragma region ChatBubble

    struct PoolableBehavior__Fields
    {
        struct MonoBehaviour__Fields _;
        void* OwnerPool;
        int32_t PoolIndex;
    };

    struct ChatBubble__Fields {
        struct PoolableBehavior__Fields _;
        void* Player; // struct PoolablePlayer
        struct SpriteRenderer* Xmark;
        struct SpriteRenderer* votedMark;
        struct TextMeshPro* NameText;
        struct TextMeshPro* TextArea;
        struct SpriteRenderer* Background;
        struct SpriteRenderer* MaskArea;
        void* PlatformIcon;
        struct TextMeshPro* ColorBlindName;
        struct GameData_PlayerInfo* playerInfo;
        int32_t maskLayer;
    };

    struct ChatBubble
    {
        struct ChatBubble__Class* klass;
        void* monitor;
        struct ChatBubble__Fields fields;
    };

    struct ChatBubble__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Reset;
    };

    struct ChatBubble__StaticFields
    {
        struct Vector3 PlayerMessageScale;
        struct Vector3 PlayerNotificationScale;
        struct Vector3 VotedAndDeadMarkerPosition;
        struct Vector3 VotedAndDeadMarkerPositionRight;
    };

    struct ChatBubble__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ChatBubble__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ChatBubble__VTable vtable;
    };
#pragma endregion

#pragma region ChatController
    struct ChatController__Fields
    {
        struct MonoBehaviour__Fields _;
        void* chatBubPool;
        struct Transform* TypingArea;
        struct SpriteRenderer* TextBubble;
        struct TextBoxTMP* TextArea;
        struct TextMeshPro* CharCount;
        int32_t MaxChat;
        void* scroller;
        struct GameObject* Content;
        struct SpriteRenderer* BackgroundImage;
        struct SpriteRenderer* ChatNotifyDot;
        struct TextMeshPro* SendRateMessage;
        struct Vector3 SourcePos;
        struct Vector3 TargetPos;
        struct Vector3 MeetingHudPos;
        void* AspectPosition;
        float TimeSinceLastMessage;
        void* MessageSound;
        void* WarningSound;
        bool animating;
        void* notificationRoutine;
        void* BanButton;
        void* quickChatMenu;
        void* quickChatData;
        struct GameObject* OpenKeyboardButton;
        struct GameObject* ChatButton;
        void* BackButton;
        void* DefaultButtonSelected;
        void* ControllerSelectable;
        void* specialInputHandler;
        void* logger;
    };

    struct ChatController
    {
        struct ChatController__Class* klass;
        void* monitor;
        struct ChatController__Fields fields;
    };

    struct ChatController__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct ChatController__StaticFields
    {
    };

    struct ChatController__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ChatController__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ChatController__VTable vtable;
    };
#pragma endregion

#pragma region PlayerMaterial
#if defined(_CPLUSPLUS_)
    enum class PlayerMaterial_MaskType__Enum : int32_t {
        None = 0x00000000,
        SimpleUI = 0x00000001,
        ComplexUI = 0x00000002,
        Exile = 0x00000003,
        ScrollingUI = 0x00000004,
    };

#else
    enum PlayerMaterial_MaskType__Enum {
        PlayerMaterial_MaskType__Enum_None = 0x00000000,
        PlayerMaterial_MaskType__Enum_SimpleUI = 0x00000001,
        PlayerMaterial_MaskType__Enum_ComplexUI = 0x00000002,
        PlayerMaterial_MaskType__Enum_Exile = 0x00000003,
        PlayerMaterial_MaskType__Enum_ScrollingUI = 0x00000004,
    };

#endif

    struct PlayerMaterial_Properties {
#if defined(_CPLUSPLUS_)
        PlayerMaterial_MaskType__Enum MaskType;
#else
        int32_t MaskType;
#endif
        int32_t MaskLayer;
        int32_t ColorId;
    };
#pragma endregion

#pragma region SkinLayer

    struct SkinLayer__Fields {
        struct MonoBehaviour__Fields _;
        struct SpriteRenderer* layer;
        void* animator;
        void* skin;
        struct PlayerMaterial_Properties matProperties;
    };

    struct SkinLayer {
        struct SkinLayer__Class* klass;
        MonitorData* monitor;
        struct SkinLayer__Fields fields;
    };

    struct SkinLayer__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct SkinLayer__StaticFields {
    };

    struct SkinLayer__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SkinLayer__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SkinLayer__VTable vtable;
    };

#pragma endregion

#pragma region PlayerPhysics

#if defined(_CPLUSPLUS_)
    enum class PlayerBodyTypes__Enum : int32_t {
        Normal = 0x00000000,
        Horse = 0x00000001,
        Seeker = 0x00000002,
    };

#else
    enum PlayerBodyTypes__Enum {
        PlayerBodyTypes__Enum_Normal = 0x00000000,
        PlayerBodyTypes__Enum_Horse = 0x00000001,
        PlayerBodyTypes__Enum_Seeker = 0x00000002,
    };

#endif

    struct PlayerPhysics__Fields {
        struct InnerNetObject__Fields _;
        uint8_t lastClimbLadderSid;
        void* ImpostorDiscoveredSound;
        void* Animations;
        void* inputHandler;
        float Speed;
        float GhostSpeed;
        void* logger;
        void* body;
        struct PlayerControl* myPlayer;
#if defined(_CPLUSPLUS_)
        PlayerBodyTypes__Enum bodyType;
#else
        int32_t bodyType;
#endif
        void* petCoroutine;
        bool _DoingCustomAnimation_k__BackingField;
    };

    struct PlayerPhysics {
        struct PlayerPhysics__Class* klass;
        MonitorData* monitor;
        struct PlayerPhysics__Fields fields;
    };

    struct PlayerPhysics__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct PlayerPhysics__StaticFields
    {
    };

    struct PlayerPhysics__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerPhysics__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerPhysics__VTable vtable;
    };
#pragma endregion

#pragma region CosmeticsLayer
    struct CosmeticsLayer__Fields {
        struct MonoBehaviour__Fields _;
        bool alwaysDrawNormalPlayer;
        bool uiPet;
        float zIndexSpacing;
        bool showColorBlindText;
        void* bodySprites;
        struct TextMeshPro* colorBlindText;
        void* hat;
        struct TextMeshPro* nameText;
        struct GameObject* nameTextContainer;
        struct Transform* petParent;
        struct SkinLayer* skin;
        void* visor;
#if defined(_CPLUSPLUS_)
        PlayerBodyTypes__Enum bodyType;
#else
        int32_t bodyType;
#endif
        struct PlayerMaterial_Properties bodyMatProperties;
        void* currentBodySprite;
        struct PetBehaviour* currentPet;
        void* normalBodySprite;
        bool initialized;
        bool visible;
        bool isNameVisible;
        bool lockVisible;
    };

    struct CosmeticsLayer__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct CosmeticsLayer__StaticFields {
    };

    struct CosmeticsLayer__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct CosmeticsLayer__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct CosmeticsLayer__VTable vtable;
    };

    struct CosmeticsLayer {
        struct CosmeticsLayer__Class* klass;
        MonitorData* monitor;
        struct CosmeticsLayer__Fields fields;
    };
#pragma endregion

#pragma region PlayerControl

    struct PlayerControl__Fields {
        struct InnerNetObject__Fields _;
        int32_t LastStartCounter;
        uint8_t PlayerId;
        struct String* FriendCode;
        struct String* Puid;
        float MaxReportDistance;
        bool moveable;
        struct CosmeticsLayer* cosmetics;
        bool ForceKillTimerContinue;
#if defined(_CPLUSPLUS_)
        PlayerOutfitType__Enum _CurrentOutfitType_k__BackingField;
#else
        int32_t _CurrentOutfitType_k__BackingField;
#endif
        bool inVent;
        bool walkingToVent;
        bool petting;
        bool inMovingPlat;
        bool onLadder;
        bool protectedByGuardianThisRound;
        bool shapeshifting;
        struct GameData_PlayerInfo* _cachedData;
        bool protectedByGuardian;
        float flashlightAngle;
        void* FootSteps;
        void* KillSfx;
        void* KillAnimations;
        float killTimer;
        int32_t RemainingEmergencies;
        void* LightPrefab;
        void* lightSource;
        struct Collider2D* Collider;
        struct PlayerPhysics* MyPhysics;
        struct CustomNetworkTransform* NetTransform;
        struct Collider2D* clickKillCollider;
        struct List_1_PlayerTask_* myTasks;
        struct Vector3 defaultPlayerScale;
        struct List_1_RoleEffectAnimation_* currentRoleAnimations;
        struct GameObject* TargetFlashlight;
        bool isDummy;
        bool notRealPlayer;
        void* logger;
        void* hitBuffer;
        void* closest;
        bool isNew;
        void* cache;
        void* itemsInRange;
        void* newItemsInRange;
        uint8_t scannerCount;
        bool roleAssigned;
    };

    struct PlayerControl {
        struct PlayerControl__Class* klass;
        MonitorData* monitor;
        struct PlayerControl__Fields fields;
    };

    struct PlayerControl__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct PlayerControl__StaticFields {
        struct PlayerControl* LocalPlayer;
        struct List_1_PlayerControl_* AllPlayerControls;
    };

    struct PlayerControl__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerControl__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerControl__VTable vtable;
    };
#pragma endregion

#pragma region PlayerControl__Array
    struct PlayerControl__Array
    {
        struct PlayerControl__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlayerControl* vector[32];
    };

    struct PlayerControl__Array__VTable
    {
    };

    struct PlayerControl__Array__StaticFields
    {
    };

    struct PlayerControl__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlayerControl__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlayerControl__Array__VTable vtable;
    };
#pragma endregion

#pragma region List_1_PlayerControl_
    struct __declspec(align(4)) List_1_PlayerControl___Fields
    {
        struct PlayerControl__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_PlayerControl_
    {
        struct List_1_PlayerControl___Class* klass;
        void* monitor;
        struct List_1_PlayerControl___Fields fields;
    };

    struct List_1_PlayerControl___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_PlayerControl___StaticFields
    {
        struct PlayerControl__Array* _emptyArray;
    };

    struct List_1_PlayerControl___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_PlayerControl___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_PlayerControl___VTable vtable;
    };
#pragma endregion

#pragma region HudManager

    struct DestroyableSingleton_1_HudManager___Fields
    {
        struct MonoBehaviour__Fields _;
        bool DontDestroy;
    };

    struct HudManager__Fields {
        struct DestroyableSingleton_1_HudManager___Fields _;
        struct FollowerCamera* PlayerCam;
        struct Camera* UICamera;
        struct MeetingHud* MeetingPrefab;
        void* KillButton;
        void* AdminButton;
        void* SabotageButton;
        void* ImpostorVentButton;
        void* UseButton;
        void* PetButton;
        void* AbilityButton;
        void* ReportButton;
        struct TextMeshPro* GameSettings;
        struct GameObject* TaskStuff;
        struct TaskPanelBehaviour* TaskPanel;
        struct CrewmatesKilledTracker* CrewmatesKilled;
        struct ChatController* Chat;
        void* Dialogue;
        struct Transform* TaskCompleteOverlay;
        float taskDirtyTimer;
        void* ShadowQuad;
        struct SpriteRenderer* FullScreen;
        void* _ReactorFlash_k__BackingField;
        void* _OxyFlash_k__BackingField;
        void* MapButton;
        void* KillOverlay;
        void* joystick;
        void* joystickR;
        void* Joysticks;
        struct MonoBehaviour* RightVJoystick;
        struct Collider2D* LeftStickDeadZone;
        struct Collider2D* RightStickDeadZone;
        void* discussEmblem;
        void* shhhEmblem;
        void* IntroPrefab;
        void* GameMenu;
        void* Notifier;
        void* roomTracker;
        void* TaskCompleteSound;
        void* TaskUpdateSound;
        struct Transform* consoleUIRoot;
        void* consoleUIObjects;
        struct GameObject* menuNavigationPrompts;
        struct GameObject* GameLoadAnimation;
        float consoleUIHorizontalShift;
        struct GameObject* playerListPrompt;
        void* AlertFlash;
        void* DangerMeter;
        struct GameObject* SettingsButton;
        void* tasksString;
        void* lightFlashHandle;
        bool _IsIntroDisplayed_k__BackingField;
    };

    struct HudManager {
        struct HudManager__Class* klass;
        MonitorData* monitor;
        struct HudManager__Fields fields;
    };

    struct HudManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct HudManager__StaticFields
    {
    };

    struct HudManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct HudManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct HudManager__VTable vtable;
    };
#pragma endregion

#pragma region Action_1_MapBehaviour_

    struct __declspec(align(4)) Delegate__Fields
    {
        void* method_ptr;
        void* invoke_impl;
        struct Object* m_target;
        void* method;
        void* delegate_trampoline;
        void* extra_arg;
        void* method_code;
        struct MethodInfo_1* method_info;
        struct MethodInfo_1* original_method_info;
        struct DelegateData* data;
        bool method_is_virtual;
    };

    struct MulticastDelegate__Fields
    {
        struct Delegate__Fields _;
        void* delegates;
    };

    struct Action_1_MapBehaviour___Fields
    {
        struct MulticastDelegate__Fields _;
    };

    struct Action_1_MapBehaviour_
    {
        struct Action_1_MapBehaviour___Class* klass;
        void* monitor;
        struct Action_1_MapBehaviour___Fields fields;
    };

    struct Action_1_MapBehaviour___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Clone;
        VirtualInvokeData GetObjectData;
        VirtualInvokeData DynamicInvokeImpl;
        VirtualInvokeData Clone_1;
        VirtualInvokeData GetMethodImpl;
        VirtualInvokeData GetObjectData_1;
        VirtualInvokeData GetInvocationList;
        VirtualInvokeData CombineImpl;
        VirtualInvokeData RemoveImpl;
        VirtualInvokeData Invoke;
        VirtualInvokeData BeginInvoke;
        VirtualInvokeData EndInvoke;
    };

    struct Action_1_MapBehaviour___StaticFields
    {
    };

    struct Action_1_MapBehaviour___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Action_1_MapBehaviour___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Action_1_MapBehaviour___VTable vtable;
    };
#pragma endregion

#pragma region KeyboardJoystick
    struct KeyboardJoystick__Fields
    {
        struct MonoBehaviour__Fields _;
        struct Vector2 del;
        void* myController;
        void* hitBuffer;
        int32_t touchId;
    };

    struct KeyboardJoystick
    {
        struct KeyboardJoystick__Class* klass;
        void* monitor;
        struct KeyboardJoystick__Fields fields;
    };

    struct KeyboardJoystick__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_DeltaL;
        VirtualInvokeData get_DeltaR;
        VirtualInvokeData ToggleVisuals;
    };

    struct KeyboardJoystick__StaticFields
    {
        void* player;
    };

    struct KeyboardJoystick__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct KeyboardJoystick__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct KeyboardJoystick__VTable vtable;
    };
#pragma endregion

#pragma region ScreenJoystick
    struct ScreenJoystick__Fields
    {
        struct MonoBehaviour__Fields _;
        void* hitBuffer;
        struct Vector2 _Delta_k__BackingField;
        void* myController;
        int32_t touchId;
    };

    struct ScreenJoystick
    {
        struct ScreenJoystick__Class* klass;
        void* monitor;
        struct ScreenJoystick__Fields fields;
    };

    struct ScreenJoystick__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_DeltaL;
        VirtualInvokeData get_DeltaR;
        VirtualInvokeData ToggleVisuals;
    };

    struct ScreenJoystick__StaticFields
    {
    };

    struct ScreenJoystick__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ScreenJoystick__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ScreenJoystick__VTable vtable;
    };
#pragma endregion

#pragma region SpriteRenderer__Array
    struct SpriteRenderer__Array
    {
        Il2CppObject obj;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct SpriteRenderer* vector[32];
    };
#pragma endregion

#pragma region List_1_UnityEngine_SpriteRenderer_
    struct __declspec(align(4)) List_1_UnityEngine_SpriteRenderer___Fields
    {
        struct SpriteRenderer__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_UnityEngine_SpriteRenderer_
    {
        void* klass;
        void* monitor;
        struct List_1_UnityEngine_SpriteRenderer___Fields fields;
    };
#pragma endregion

#pragma region VoteSpreader
    struct VoteSpreader__Fields {
        struct MonoBehaviour__Fields _;
        struct List_1_UnityEngine_SpriteRenderer_* Votes;
        void* VoteRange;
        int32_t maxVotesBeforeSmoosh;
        float CounterY;
        float adjustRate;
    };

    struct VoteSpreader {
        struct VoteSpreader__Class* klass;
        MonitorData* monitor;
        struct VoteSpreader__Fields fields;
    };

    struct VoteSpreader__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct VoteSpreader__StaticFields {
    };

    struct VoteSpreader__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct VoteSpreader__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct VoteSpreader__VTable vtable;
    };
#pragma endregion

#pragma region MeetingHud

#if defined(_CPLUSPLUS_)
    enum class MeetingHud_VoteStates__Enum : int32_t
    {
        Animating = 0x00000000,
        Discussion = 0x00000001,
        NotVoted = 0x00000002,
        Voted = 0x00000003,
        Results = 0x00000004,
        Proceeding = 0x00000005,
    };

#else
    enum MeetingHud_VoteStates__Enum
    {
        MeetingHud_VoteStates__Enum_Animating = 0x00000000,
        MeetingHud_VoteStates__Enum_Discussion = 0x00000001,
        MeetingHud_VoteStates__Enum_NotVoted = 0x00000002,
        MeetingHud_VoteStates__Enum_Voted = 0x00000003,
        MeetingHud_VoteStates__Enum_Results = 0x00000004,
        MeetingHud_VoteStates__Enum_Proceeding = 0x00000005,
    };

#endif

    struct MeetingHud__Fields
    {
        struct InnerNetObject__Fields _;
        struct SpriteRenderer* BlackBackground;
        void* PlayerColoredParts;
        void* MeetingIntro;
        struct Transform* ButtonParent;
        struct TextMeshPro* TitleText;
        struct Vector3 VoteOrigin;
        struct Vector3 VoteButtonOffsets;
        void* SkipVoteButton;
        struct PlayerVoteArea__Array* playerStates;
        void* PlayerButtonPrefab;
        struct SpriteRenderer* PlayerVotePrefab;
        void* CrackedGlass;
        struct SpriteRenderer* Glass;
        void* ProceedButton;
        void* VoteSound;
        void* VoteLockinSound;
        void* VoteEndingSound;
#if defined(_CPLUSPLUS_)
        MeetingHud_VoteStates__Enum state;
#else
        int32_t state;
#endif
        struct GameObject* SkippedVoting;
        struct SpriteRenderer* HostIcon;
        struct GameData_PlayerInfo* exiledPlayer;
        bool wasTie;
        struct TextMeshPro* TimerText;
        float discussionTimer;
        uint8_t reporterId;
        bool amDead;
        float resultsStartedAt;
        int32_t lastSecond;
        void* logger;
        void* DefaultButtonSelected;
        void* ProceedButtonUi;
        void* ControllerSelectable;
    };

    struct MeetingHud
    {
        struct MeetingHud__Class* klass;
        void* monitor;
        struct MeetingHud__Fields fields;
    };

    struct MeetingHud__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData HandleDisconnect;
        VirtualInvokeData HandleDisconnect_1;
    };

    struct MeetingHud__StaticFields
    {
        struct MeetingHud* Instance;
    };

    struct MeetingHud__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MeetingHud__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MeetingHud__VTable vtable;
    };
#pragma endregion

#pragma region CustomNetworkTransform
    struct CustomNetworkTransform__Fields {
        struct InnerNetObject__Fields _;
        float sendInterval;
        float snapThreshold;
        float interpolateMovement;
        struct PlayerControl* myPlayer;
        void* body;
        struct Vector2 targetSyncPosition;
        struct Vector2 targetSyncVelocity;
        uint16_t lastSequenceId;
        struct Vector2 prevPosSent;
        struct Vector2 prevVelSent;
    };

    struct CustomNetworkTransform
    {
        struct CustomNetworkTransform__Class* klass;
        void* monitor;
        struct CustomNetworkTransform__Fields fields;
    };

    struct CustomNetworkTransform__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct CustomNetworkTransform__StaticFields
    {
    };

    struct CustomNetworkTransform__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct CustomNetworkTransform__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct CustomNetworkTransform__VTable vtable;
    };
#pragma endregion

#pragma region MainMenuManager
    struct MainMenuManager__Fields {
        struct MonoBehaviour__Fields _;
        void* AdsPolicy;
        void* Announcement;
        void* googlePlayAssetHandler;
        struct HatManager* HatManagerRef;
        void* CosmicubeManagerRef;
        void* playerCustomizationPrefab;
        void* DefaultButtonSelected;
        void* ControllerSelectable;
        void* disableOnStartup;
        struct GameObject* NewStoreItemsIcon;
        void* cosmicubeManager;
    };

    struct MainMenuManager {
        struct MainMenuManager__Class* klass;
        MonitorData* monitor;
        struct MainMenuManager__Fields fields;
    };

    struct MainMenuManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct MainMenuManager__StaticFields
    {
    };

    struct MainMenuManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct MainMenuManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct MainMenuManager__VTable vtable;
    };
#pragma endregion

#pragma region DisconnectReasons__Enum
#if defined(_CPLUSPLUS_)
    enum class DisconnectReasons__Enum : int32_t {
        ExitGame = 0x00000000,
        GameFull = 0x00000001,
        GameStarted = 0x00000002,
        GameNotFound = 0x00000003,
        IncorrectVersion = 0x00000005,
        Banned = 0x00000006,
        Kicked = 0x00000007,
        Custom = 0x00000008,
        InvalidName = 0x00000009,
        Hacking = 0x0000000a,
        NotAuthorized = 0x0000000b,
        ConnectionLimit = 0x0000000c,
        Destroy = 0x00000010,
        Error = 0x00000011,
        IncorrectGame = 0x00000012,
        ServerRequest = 0x00000013,
        ServerFull = 0x00000014,
        InternalPlayerMissing = 0x00000064,
        InternalNonceFailure = 0x00000065,
        InternalConnectionToken = 0x00000066,
        PlatformLock = 0x00000067,
        LobbyInactivity = 0x00000068,
        MatchmakerInactivity = 0x00000069,
        InvalidGameOptions = 0x0000006a,
        NoServersAvailable = 0x0000006b,
        QuickmatchDisabled = 0x0000006c,
        TooManyGames = 0x0000006d,
        QuickchatLock = 0x0000006e,
        MatchmakerFull = 0x0000006f,
        Sanctions = 0x00000070,
        ServerError = 0x00000071,
        SelfPlatformLock = 0x00000072,
        DuplicateConnectionDetected = 0x00000073,
        TooManyRequests = 0x00000074,
        IntentionalLeaving = 0x000000d0,
        FocusLostBackground = 0x000000cf,
        FocusLost = 0x000000d1,
        NewConnection = 0x000000d2,
        PlatformParentalControlsBlock = 0x000000d3,
        PlatformUserBlock = 0x000000d4,
        PlatformFailedToGetUserBlock = 0x000000d5,
        Unknown = 0x000000ff,
    };

#else
    enum DisconnectReasons__Enum {
        DisconnectReasons__Enum_ExitGame = 0x00000000,
        DisconnectReasons__Enum_GameFull = 0x00000001,
        DisconnectReasons__Enum_GameStarted = 0x00000002,
        DisconnectReasons__Enum_GameNotFound = 0x00000003,
        DisconnectReasons__Enum_IncorrectVersion = 0x00000005,
        DisconnectReasons__Enum_Banned = 0x00000006,
        DisconnectReasons__Enum_Kicked = 0x00000007,
        DisconnectReasons__Enum_Custom = 0x00000008,
        DisconnectReasons__Enum_InvalidName = 0x00000009,
        DisconnectReasons__Enum_Hacking = 0x0000000a,
        DisconnectReasons__Enum_NotAuthorized = 0x0000000b,
        DisconnectReasons__Enum_ConnectionLimit = 0x0000000c,
        DisconnectReasons__Enum_Destroy = 0x00000010,
        DisconnectReasons__Enum_Error = 0x00000011,
        DisconnectReasons__Enum_IncorrectGame = 0x00000012,
        DisconnectReasons__Enum_ServerRequest = 0x00000013,
        DisconnectReasons__Enum_ServerFull = 0x00000014,
        DisconnectReasons__Enum_InternalPlayerMissing = 0x00000064,
        DisconnectReasons__Enum_InternalNonceFailure = 0x00000065,
        DisconnectReasons__Enum_InternalConnectionToken = 0x00000066,
        DisconnectReasons__Enum_PlatformLock = 0x00000067,
        DisconnectReasons__Enum_LobbyInactivity = 0x00000068,
        DisconnectReasons__Enum_MatchmakerInactivity = 0x00000069,
        DisconnectReasons__Enum_InvalidGameOptions = 0x0000006a,
        DisconnectReasons__Enum_NoServersAvailable = 0x0000006b,
        DisconnectReasons__Enum_QuickmatchDisabled = 0x0000006c,
        DisconnectReasons__Enum_TooManyGames = 0x0000006d,
        DisconnectReasons__Enum_QuickchatLock = 0x0000006e,
        DisconnectReasons__Enum_MatchmakerFull = 0x0000006f,
        DisconnectReasons__Enum_Sanctions = 0x00000070,
        DisconnectReasons__Enum_ServerError = 0x00000071,
        DisconnectReasons__Enum_SelfPlatformLock = 0x00000072,
        DisconnectReasons__Enum_DuplicateConnectionDetected = 0x00000073,
        DisconnectReasons__Enum_TooManyRequests = 0x00000074,
        DisconnectReasons__Enum_IntentionalLeaving = 0x000000d0,
        DisconnectReasons__Enum_FocusLostBackground = 0x000000cf,
        DisconnectReasons__Enum_FocusLost = 0x000000d1,
        DisconnectReasons__Enum_NewConnection = 0x000000d2,
        DisconnectReasons__Enum_PlatformParentalControlsBlock = 0x000000d3,
        DisconnectReasons__Enum_PlatformUserBlock = 0x000000d4,
        DisconnectReasons__Enum_PlatformFailedToGetUserBlock = 0x000000d5,
        DisconnectReasons__Enum_Unknown = 0x000000ff,
    };

#endif
#pragma endregion

#pragma region InnerNetClient

#if defined(_CPLUSPLUS_)
    enum class MatchMakerModes__Enum : int32_t
    {
        None = 0x00000000,
        Client = 0x00000001,
        HostAndClient = 0x00000002,
    };

#else
    enum MatchMakerModes__Enum
    {
        MatchMakerModes__Enum_None = 0x00000000,
        MatchMakerModes__Enum_Client = 0x00000001,
        MatchMakerModes__Enum_HostAndClient = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class GameModes__Enum : uint8_t {
        None = 0x00,
        Normal = 0x01,
        HideNSeek = 0x02,
    };

#else
    enum GameModes__Enum {
        GameModes__Enum_None = 0x00,
        GameModes__Enum_Normal = 0x01,
        GameModes__Enum_HideNSeek = 0x02,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class NetworkModes__Enum : int32_t {
        LocalGame = 0x00000000,
        OnlineGame = 0x00000001,
        FreePlay = 0x00000002,
    };

#else
    enum NetworkModes__Enum {
        NetworkModes__Enum_LocalGame = 0x00000000,
        NetworkModes__Enum_OnlineGame = 0x00000001,
        NetworkModes__Enum_FreePlay = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class InnerNetClient_GameStates__Enum : int32_t
    {
        NotJoined = 0x00000000,
        Joined = 0x00000001,
        Started = 0x00000002,
        Ended = 0x00000003,
    };

#else
    enum InnerNetClient_GameStates__Enum
    {
        InnerNetClient_GameStates__Enum_NotJoined = 0x00000000,
        InnerNetClient_GameStates__Enum_Joined = 0x00000001,
        InnerNetClient_GameStates__Enum_Started = 0x00000002,
        InnerNetClient_GameStates__Enum_Ended = 0x00000003,
    };

#endif

    struct InnerNetClient__Fields {
        struct MonoBehaviour__Fields _;
        float MinSendInterval;
        uint32_t NetIdCnt;
        float timer;
        void* SpawnableObjects;
        void* NonAddressableSpawnableObjects;
        bool InOnlineScene;
        void* DestroyedObjects;
        void* allObjects;
        void* allObjectsFast;
        void* Streams;
        int32_t msgNum;
        void* serverLogger;
        struct String* networkAddress;
        int32_t networkPort;
        bool useDtls;
        void* connection;
#if defined(_CPLUSPLUS_)
        MatchMakerModes__Enum mode;
#else
        int32_t mode;
#endif
#if defined(_CPLUSPLUS_)
        NetworkModes__Enum NetworkMode;
#else
        int32_t NetworkMode;
#endif
        int32_t GameId;
        int32_t HostId;
        int32_t ClientId;
        struct List_1_InnerNet_ClientData_* allClients;
        void* recentClients;
#if defined(_CPLUSPLUS_)
        DisconnectReasons__Enum LastDisconnectReason;
#else
        int32_t LastDisconnectReason;
#endif
        struct String* LastCustomDisconnect;
        uint8_t LastServerChatMode;
        void* LastMatchmakerError;
        void* PreSpawnDispatcher;
        void* Dispatcher;
        void* gameOptionsFactory;
        bool _IsGamePublic_k__BackingField;
#if defined(_CPLUSPLUS_)
        InnerNetClient_GameStates__Enum GameState;
#else
        int32_t GameState;
#endif
        bool isConnecting;
        bool platformSpecificsChecked;
        void* TempQueue;
        bool appPaused;
    };

    struct InnerNetClient
    {
        struct InnerNetClient__Class* klass;
        void* monitor;
        struct InnerNetClient__Fields fields;
    };

    struct InnerNetClient__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Start;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData OnApplicationPause;
        VirtualInvokeData __unknown;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData __unknown_6;
        VirtualInvokeData __unknown_7;
        VirtualInvokeData __unknown_8;
        VirtualInvokeData __unknown_9;
        VirtualInvokeData __unknown_10;
        VirtualInvokeData __unknown_11;
    };

    struct InnerNetClient__StaticFields
    {
        void* disconnectReasons;
        int32_t SecondsSuspendedBeforeDisconnect;
    };

    struct InnerNetClient__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct InnerNetClient__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct InnerNetClient__VTable vtable;
    };
#pragma endregion

#pragma region AmongUsClient

#if defined(_CPLUSPLUS_)
    enum class DiscoveryState__Enum : int32_t
    {
        Off = 0x00000000,
        Broadcast = 0x00000001,
    };

#else
    enum DiscoveryState__Enum
    {
        DiscoveryState__Enum_Off = 0x00000000,
        DiscoveryState__Enum_Broadcast = 0x00000001,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class CrossplayPrivilegeErrorType__Enum : int32_t {
        None = 0x00000000,
        Crossplay = 0x00000001,
        CrossplayCommunication = 0x00000002,
    };

#else
    enum CrossplayPrivilegeErrorType__Enum {
        CrossplayPrivilegeErrorType__Enum_None = 0x00000000,
        CrossplayPrivilegeErrorType__Enum_Crossplay = 0x00000001,
        CrossplayPrivilegeErrorType__Enum_CrossplayCommunication = 0x00000002,
    };

#endif

    struct AmongUsClient__Fields {
        struct InnerNetClient__Fields _;
        struct String* OnlineScene;
        struct String* MainMenuScene;
        struct GameData* GameDataPrefab;
        struct PlayerControl* PlayerPrefab;
        void* ShipPrefabs;
        int32_t TutorialMapId;
        float SpawnRadius;
#if defined(_CPLUSPLUS_)
        DiscoveryState__Enum discoverState;
#else
        int32_t discoverState;
#endif
        void* DisconnectHandlers;
        void* GameListHandlers;
#if defined(_CPLUSPLUS_)
        CrossplayPrivilegeErrorType__Enum CrossplayPrivilegeError;
#else
        int32_t CrossplayPrivilegeError;
#endif
        int32_t MAX_CLIENT_WAIT_TIME;
        void* logger;
    };

    struct AmongUsClient {
        struct AmongUsClient__Class* klass;
        MonitorData* monitor;
        struct AmongUsClient__Fields fields;
    };

    struct AmongUsClient__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Start;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData OnApplicationPause;
        VirtualInvokeData OnGameCreated;
        VirtualInvokeData OnGameJoined;
        VirtualInvokeData OnWaitForHost;
        VirtualInvokeData CoStartGame;
        VirtualInvokeData OnGameEnd;
        VirtualInvokeData OnBecomeHost;
        VirtualInvokeData OnPlayerJoined;
        VirtualInvokeData CoOnPlayerChangedScene;
        VirtualInvokeData OnPlayerLeft;
        VirtualInvokeData OnReportedPlayer;
        VirtualInvokeData OnDisconnected;
        VirtualInvokeData OnGetGameList;
    };

    struct AmongUsClient__StaticFields
    {
        struct AmongUsClient* Instance;
    };

    struct AmongUsClient__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct AmongUsClient__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct AmongUsClient__VTable vtable;
    };
#pragma endregion

#pragma region ClientData
    struct __declspec(align(4)) ClientData__Fields
    {
        int32_t Id;
        bool InScene;
        bool IsReady;
        bool HasBeenReported;
        struct PlayerControl* Character;
        uint32_t PlayerLevel;
        void* PlatformData;
        struct String* PlayerName;
        struct String* ProductUserId;
        struct String* FriendCode;
        int32_t ColorId;
    };

    struct ClientData
    {
        struct ClientData__Class* klass;
        void* monitor;
        struct ClientData__Fields fields;
    };

    struct ClientData__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct ClientData__StaticFields
    {
    };

    struct ClientData__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ClientData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ClientData__VTable vtable;
    };
#pragma endregion

#pragma region ClientData__Array
    struct ClientData__Array
    {
        struct ClientData__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct ClientData* vector[32];
    };
    struct ClientData__Array__VTable
    {
    };

    struct ClientData__Array__StaticFields
    {
    };

    struct ClientData__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ClientData__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ClientData__Array__VTable vtable;
    };
#pragma endregion

#pragma region List_1_InnerNet_ClientData_
    struct __declspec(align(4)) List_1_InnerNet_ClientData___Fields
    {
        struct ClientData__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_InnerNet_ClientData_
    {
        struct List_1_InnerNet_ClientData___Class* klass;
        void* monitor;
        struct List_1_InnerNet_ClientData___Fields fields;
    };
    struct List_1_InnerNet_ClientData___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_InnerNet_ClientData___StaticFields
    {
        struct ClientData__Array* _emptyArray;
    };

    struct List_1_InnerNet_ClientData___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_InnerNet_ClientData___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_InnerNet_ClientData___VTable vtable;
    };
#pragma endregion

#pragma region LobbyBehaviour
    struct LobbyBehaviour__Fields
    {
        struct InnerNetObject__Fields _;
        void* SpawnSound;
        void* SpawnInClip;
        void* SpawnPositions;
        void* DropShipSound;
        void* AllRooms;
        float timer;
    };

    struct LobbyBehaviour
    {
        struct LobbyBehaviour__Class* klass;
        void* monitor;
        struct LobbyBehaviour__Fields fields;
    };

    struct LobbyBehaviour__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
    };

    struct LobbyBehaviour__StaticFields
    {
        struct LobbyBehaviour* Instance;
    };

    struct LobbyBehaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct LobbyBehaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct LobbyBehaviour__VTable vtable;
    };
#pragma endregion

#pragma region NoShadowBehaviour
    struct NoShadowBehaviour__Fields
    {
        struct MonoBehaviour__Fields _;
        struct Renderer* rend;
        bool didHit;
        struct Renderer* shadowChild;
        void* hitOverride;
        void* bc;
        bool isBox;
        bool verticalBox;
        void* boxCheckPoints;
    };

    struct NoShadowBehaviour
    {
        struct NoShadowBehaviour__Class* klass;
        void* monitor;
        struct NoShadowBehaviour__Fields fields;
    };

    struct NoShadowBehaviour__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct NoShadowBehaviour__StaticFields
    {
    };

    struct NoShadowBehaviour__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct NoShadowBehaviour__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct NoShadowBehaviour__VTable vtable;
    };
#pragma endregion

#pragma region PolusShipStatus
    struct PolusShipStatus__Fields
    {
        struct ShipStatus__Fields _;
    };

    struct PolusShipStatus
    {
        struct PolusShipStatus__Class* klass;
        void* monitor;
        struct PolusShipStatus__Fields fields;
    };

    struct PolusShipStatus__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData CompareTo;
        VirtualInvokeData get_IsDirty;
        VirtualInvokeData get_Chunked;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData HandleRpc;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData OnEnable;
        VirtualInvokeData RepairGameOverSystems;
        VirtualInvokeData Start;
        VirtualInvokeData SpawnPlayer;
        VirtualInvokeData OnMeetingCalled;
        VirtualInvokeData PrespawnStep;
        VirtualInvokeData CalculateLightRadius;
    };

    struct PolusShipStatus__StaticFields
    {
    };

    struct PolusShipStatus__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PolusShipStatus__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PolusShipStatus__VTable vtable;
    };
#pragma endregion

#pragma region DoorBreakerGame
    struct DoorBreakerGame__Fields
    {
        struct Minigame__Fields _;
        struct PlainDoor* MyDoor;
        void* Buttons;
        void* FlipSound;
    };

    struct DoorBreakerGame
    {
        struct DoorBreakerGame__Class* klass;
        void* monitor;
        struct DoorBreakerGame__Fields fields;
    };

    struct DoorBreakerGame__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Begin;
        VirtualInvokeData Close;
        VirtualInvokeData CoAnimateOpen;
        VirtualInvokeData CoDestroySelf;
        VirtualInvokeData SetDoor;
    };

    struct DoorBreakerGame__StaticFields
    {
    };

    struct DoorBreakerGame__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct DoorBreakerGame__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct DoorBreakerGame__VTable vtable;
    };
#pragma endregion

#pragma region SabotageTask
    struct SabotageTask__Fields
    {
        struct PlayerTask__Fields _;
        bool didContribute;
        void* Arrows;
    };

    struct SabotageTask
    {
        struct SabotageTask__Class* klass;
        void* monitor;
        struct SabotageTask__Fields fields;
    };
    struct SabotageTask__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData __unknown;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData OnRemove;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData GetMinigamePrefab;
    };

    struct SabotageTask__StaticFields
    {
    };

    struct SabotageTask__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SabotageTask__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SabotageTask__VTable vtable;
    };
#pragma endregion

#pragma region ElectricTask
    struct ElectricTask__Fields
    {
        struct SabotageTask__Fields _;
        bool isComplete;
        struct SwitchSystem* system;
        bool even;
    };

    struct ElectricTask
    {
        struct ElectricTask__Class* klass;
        void* monitor;
        struct ElectricTask__Fields fields;
    };
    struct ElectricTask__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_TaskStep;
        VirtualInvokeData get_IsComplete;
        VirtualInvokeData Initialize;
        VirtualInvokeData OnRemove;
        VirtualInvokeData ValidConsole;
        VirtualInvokeData Complete;
        VirtualInvokeData AppendTaskText;
        VirtualInvokeData GetMinigamePrefab;
    };

    struct ElectricTask__StaticFields
    {
    };

    struct ElectricTask__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ElectricTask__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ElectricTask__VTable vtable;
    };
#pragma endregion

#pragma region DeadBody
    struct DeadBody__Fields {
        struct MonoBehaviour__Fields _;
        bool Reported;
        uint8_t ParentId;
        struct Collider2D* myCollider;
        struct SpriteRenderer* bloodSplatter;
        struct SpriteRenderer* bodyRenderer;
    };

    struct DeadBody
    {
        struct DeadBody__Class* klass;
        void* monitor;
        struct DeadBody__Fields fields;
    };

    struct DeadBody__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct DeadBody__StaticFields
    {
    };

    struct DeadBody__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct DeadBody__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct DeadBody__VTable vtable;
    };
#pragma endregion

#pragma region DeadBody__Array
    struct DeadBody__Array
    {
        struct DeadBody__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct DeadBody* vector[32];
    };

    struct DeadBody__Array__VTable
    {
    };

    struct DeadBody__Array__StaticFields
    {
    };

    struct DeadBody__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct DeadBody__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct DeadBody__Array__VTable vtable;
    };
#pragma endregion

#pragma region PetData__Array
    struct PetData__Array
    {
        struct PetData__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PetData* vector[32];
    };

    struct PetData__Array__VTable
    {
    };

    struct PetData__Array__StaticFields
    {
    };

    struct PetData__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PetData__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PetData__Array__VTable vtable;
    };
#pragma endregion

#pragma region ScriptableObject
    struct ScriptableObject__Fields
    {
        struct Object_1__Fields _;
    };

    struct ScriptableObject
    {
        struct ScriptableObject__Class* klass;
        MonitorData* monitor;
        struct ScriptableObject__Fields fields;
    };

    struct ScriptableObject__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct ScriptableObject__StaticFields
    {
    };

    struct ScriptableObject__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct ScriptableObject__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct ScriptableObject__VTable vtable;
    };
#pragma endregion

#pragma region LimitedTime
    struct LimitedTime {
        int32_t limitedDay;
        int32_t limitedMonth;
        int32_t limitedYear;
        int32_t limitedHour;
        int32_t limitedMinute;
    };

#pragma endregion

#pragma region LimitedTimeStartEnd
    struct LimitedTimeStartEnd {
        struct LimitedTime timeStart;
        struct LimitedTime timeEnd;
    };
#pragma endregion

#pragma region CosmeticData
    struct CosmeticData__Fields
    {
        struct ScriptableObject__Fields _;
        void* unlockOnSelectPlatforms;
        bool freeRedeemableCosmetic;
        int32_t redeemPopUpColor;
        struct String* epicId;
        struct String* BundleId;
        struct String* ProductId;
        struct Vector2 ChipOffset;
        int32_t beanCost;
        int32_t starCost;
        bool paidOnMobile;
        struct LimitedTimeStartEnd limitedTime;
        int32_t displayOrder;
        bool NotInStore;
        bool Free;
    };
    struct CosmeticData
    {
        struct CosmeticData__Class* klass;
        MonitorData* monitor;
        struct CosmeticData__Fields fields;
    };
    struct CosmeticData__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_ProdId;
        VirtualInvokeData get_BeanCost;
        VirtualInvokeData get_StarCost;
        VirtualInvokeData get_PaidOnMobile;
        VirtualInvokeData get_LimitedTimeAvailable;
        VirtualInvokeData PreviewOnPlayer;
        VirtualInvokeData GetItemCategory;
        VirtualInvokeData SetProdId;
        VirtualInvokeData CoLoadIcon;
    };

    struct CosmeticData__StaticFields
    {
    };

    struct CosmeticData__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct CosmeticData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct CosmeticData__VTable vtable;
    };
#pragma endregion

#pragma region HatData

    struct HatData__Fields {
        struct CosmeticData__Fields _;
        void* ViewDataRef;
        bool InFront;
        bool NoBounce;
        bool BlocksVisors;
        struct String* StoreName;
        struct SkinData* RelatedSkin;
        void* hatViewData;
    };

    struct HatData {
        struct HatData__Class* klass;
        MonitorData* monitor;
        struct HatData__Fields fields;
    };

    struct HatData__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_ProdId;
        VirtualInvokeData get_BeanCost;
        VirtualInvokeData get_StarCost;
        VirtualInvokeData get_PaidOnMobile;
        VirtualInvokeData get_LimitedTimeAvailable;
        VirtualInvokeData PreviewOnPlayer;
        VirtualInvokeData GetItemCategory;
        VirtualInvokeData SetProdId;
        VirtualInvokeData CoLoadIcon;
    };

    struct HatData__StaticFields {
    };

    struct HatData__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct HatData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct HatData__VTable vtable;
    };

#pragma endregion

#pragma region HatData__Array

    struct HatData__Array {
        struct HatData__Array__Class* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct HatData* vector[32];
    };

    struct HatData__Array__VTable {
    };

    struct HatData__Array__StaticFields {
    };

    struct HatData__Array__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct HatData__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct HatData__Array__VTable vtable;
    };

#pragma endregion

#pragma region List_1_HatData_

    struct __declspec(align(4)) List_1_HatData___Fields {
        struct HatData__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_HatData_ {
        struct List_1_HatData___Class* klass;
        MonitorData* monitor;
        struct List_1_HatData___Fields fields;
    };

    struct List_1_HatData___VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_HatData___StaticFields {
        struct HatData__Array* _emptyArray;
    };

    struct List_1_HatData___Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_HatData___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_HatData___VTable vtable;
    };

#pragma endregion

#pragma region HatManager

    struct DestroyableSingleton_1_HatManager___Fields
    {
        struct MonoBehaviour__Fields _;
        bool DontDestroy;
    };

    struct HatManager__Fields
    {
        struct DestroyableSingleton_1_HatManager___Fields _;
        void* DefaultShader;
        void* PlayerMaterial;
        void* MaskedPlayerMaterial;
        void* MaskedMaterial;
        void* Groups;
        struct PetData__Array* allPets;
        struct HatData__Array* allHats;
        struct SkinData__Array* allSkins;
        void* allVisors;
        void* allNamePlates;
        void* allStarBundles;
        void* allBundles;
        void* allFeaturedItems;
        void* allFeaturedBundles;
        void* allFeaturedCubes;
    };

    struct HatManager
    {
        struct HatManager__Class* klass;
        void* monitor;
        struct HatManager__Fields fields;
    };

    struct HatManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct HatManager__StaticFields
    {
    };

    struct HatManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct HatManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct HatManager__VTable vtable;
    };
#pragma endregion

#pragma region NamePlateData
    struct NamePlateData__Fields {
        struct CosmeticData__Fields _;
        void* ViewDataRef;
        void* viewData;
    };

    struct NamePlateData {
        void* klass;
        MonitorData* monitor;
        struct NamePlateData__Fields fields;
    };
#pragma endregion

#pragma region VisorData
    struct VisorData__Fields {
        struct CosmeticData__Fields _;
        void* ViewDataRef;
        void* viewData;
    };

    struct VisorData {
        void* klass;
        MonitorData* monitor;
        struct VisorData__Fields fields;
    };
#pragma endregion

#pragma region PetData
    struct PetBehaviour__Fields {
        struct MonoBehaviour__Fields _;
        struct PetData* Data;
        struct PlayerControl* Source;
        float YOffset;
        void* animator;
        void* rend;
        void* shadowRend;
        void* body;
        struct Collider2D* Collider;
        struct Transform* PettingHandPosition;
        void* idleClip;
        void* sadClip;
        void* scaredClip;
        void* walkClip;
        void* petClip;
        bool beingPet;
    };

    struct PetBehaviour {
        void* klass;
        MonitorData* monitor;
        struct PetBehaviour__Fields fields;
    };

    struct PetData__Fields {
        struct CosmeticData__Fields _;
#if defined(_CPLUSPLUS_)
        StringNames__Enum StoreName;
#else
        int32_t StoreName;
#endif
        void* PetPrefabRef;
        void* viewData;
    };

    struct PetData {
        void* klass;
        MonitorData* monitor;
        struct PetData__Fields fields;
    };
#pragma endregion

#pragma region List_1_PetData_
    struct __declspec(align(4)) List_1_PetData___Fields {
        struct PetData__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_PetData_ {
        struct List_1_PetData___Class* klass;
        MonitorData* monitor;
        struct List_1_PetData___Fields fields;
    };

    struct IEnumerator_1_PetData_ {
        struct IEnumerator_1_PetData___Class* klass;
        MonitorData* monitor;
    };
#pragma endregion

#pragma region SkinData
    struct SkinData__Fields
    {
        struct CosmeticData__Fields _;
        void* ViewDataRef;
        struct String* StoreName;
        void* viewData;
    };

    struct SkinData
    {
        struct SkinData__Class* klass;
        void* monitor;
        struct SkinData__Fields fields;
    };
    struct SkinData__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_ProdId;
        VirtualInvokeData get_BeanCost;
        VirtualInvokeData get_StarCost;
        VirtualInvokeData get_PaidOnMobile;
        VirtualInvokeData get_LimitedTimeAvailable;
        VirtualInvokeData PreviewOnPlayer;
        VirtualInvokeData GetItemCategory;
        VirtualInvokeData SetProdId;
        VirtualInvokeData CoLoadIcon;
    };

    struct SkinData__StaticFields
    {
    };

    struct SkinData__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SkinData__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SkinData__VTable vtable;
    };
#pragma endregion

#pragma region SkinData__Array
    struct SkinData__Array
    {
        struct SkinData__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct SkinData* vector[32];
    };

    struct SkinData__Array__VTable
    {
    };

    struct SkinData__Array__StaticFields
    {
    };

    struct SkinData__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct SkinData__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct SkinData__Array__VTable vtable;
    };
#pragma endregion

#pragma region List_1_SkinData_
    struct __declspec(align(4)) List_1_SkinData___Fields
    {
        struct SkinData__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_SkinData_
    {
        struct List_1_SkinData___Class* klass;
        MonitorData* monitor;
        struct List_1_SkinData___Fields fields;
    };
    struct List_1_SkinData___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_SkinData___StaticFields
    {
        struct SkinData__Array* _emptyArray;
    };

    struct List_1_SkinData___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_SkinData___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_SkinData___VTable vtable;
    };
#pragma endregion

#pragma region IRoleOptionsCollection
    struct IRoleOptionsCollection {
        struct IRoleOptionsCollection__Class* klass;
        MonitorData* monitor;
    };

    struct IRoleOptionsCollection__VTable {
        VirtualInvokeData GetNumPerGame;
        VirtualInvokeData GetChancePerGame;
        VirtualInvokeData SetRoleRate;
        VirtualInvokeData SetRoleRecommended;
    };

    struct IRoleOptionsCollection__StaticFields {
    };

    struct IRoleOptionsCollection__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct IRoleOptionsCollection__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct IRoleOptionsCollection__VTable vtable;
    };
#pragma endregion

#pragma region LogicOptions
    struct LogicOptions {
        struct LogicOptions__Class* klass;
        MonitorData* monitor;
        //struct LogicOptions__Fields fields;
    };

    struct LogicOptions__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData __unknown;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData OnPlayerDisconnect;
        VirtualInvokeData HandleRPC;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData GetAdjustedNumImpostors;
        VirtualInvokeData SetRecommendations;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData GetGhostsDoTasks;
        VirtualInvokeData GetEngineerCooldown;
        VirtualInvokeData GetEngineerInVentTime;
        VirtualInvokeData GetGuardianAngelCooldown;
        VirtualInvokeData GetShapeshifterDuration;
        VirtualInvokeData GetShapeshifterCooldown;
        VirtualInvokeData GetShapeshifterLeaveSkin;
        VirtualInvokeData GetScientistCooldown;
        VirtualInvokeData GetScientistBatteryCharge;
        VirtualInvokeData GetKillCooldown;
        VirtualInvokeData GetKillDistance;
        VirtualInvokeData GetPlayerSpeedMod;
        VirtualInvokeData GetConfirmImpostor;
        VirtualInvokeData GetEmergencyCooldown;
        VirtualInvokeData GetNumEmergencyMeetings;
        VirtualInvokeData GetVisualTasks;
        VirtualInvokeData GetAnonymousVotes;
        VirtualInvokeData GetTaskBarMode;
        VirtualInvokeData GetShowCrewmateNames;
    };

    struct LogicOptions__StaticFields {
    };

    struct LogicOptions__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct LogicOptions__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct LogicOptions__VTable vtable;
    };
#pragma endregion

#pragma region IGameOptions

#if defined(_CPLUSPLUS_)
    enum class TaskBarMode__Enum : int32_t
    {
        Normal = 0x00000000,
        MeetingOnly = 0x00000001,
        Invisible = 0x00000002,
    };

#else
    enum TaskBarMode__Enum
    {
        TaskBarMode__Enum_Normal = 0x00000000,
        TaskBarMode__Enum_MeetingOnly = 0x00000001,
        TaskBarMode__Enum_Invisible = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class ByteOptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        MapId = 0x00000001,
    };

#else
    enum ByteOptionNames__Enum {
        ByteOptionNames__Enum_Invalid = 0x00000000,
        ByteOptionNames__Enum_MapId = 0x00000001,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class FloatOptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        KillCooldown = 0x00000001,
        PlayerSpeedMod = 0x00000002,
        ImpostorLightMod = 0x00000003,
        CrewLightMod = 0x00000004,
        CrewmateTimeInVent = 0x00000064,
        FinalEscapeTime = 0x00000065,
        EscapeTime = 0x00000066,
        SeekerFinalSpeed = 0x00000067,
        MaxPingTime = 0x00000068,
        CrewmateFlashlightSize = 0x00000069,
        ImpostorFlashlightSize = 0x0000006a,
        ShapeshifterCooldown = 0x000003e8,
        ShapeshifterDuration = 0x000003e9,
        ProtectionDurationSeconds = 0x0000044c,
        GuardianAngelCooldown = 0x0000044d,
        ScientistCooldown = 0x000004b0,
        ScientistBatteryCharge = 0x000004b1,
        EngineerCooldown = 0x00000514,
        EngineerInVentMaxTime = 0x00000515,
    };

#else
    enum FloatOptionNames__Enum {
        FloatOptionNames__Enum_Invalid = 0x00000000,
        FloatOptionNames__Enum_KillCooldown = 0x00000001,
        FloatOptionNames__Enum_PlayerSpeedMod = 0x00000002,
        FloatOptionNames__Enum_ImpostorLightMod = 0x00000003,
        FloatOptionNames__Enum_CrewLightMod = 0x00000004,
        FloatOptionNames__Enum_CrewmateTimeInVent = 0x00000064,
        FloatOptionNames__Enum_FinalEscapeTime = 0x00000065,
        FloatOptionNames__Enum_EscapeTime = 0x00000066,
        FloatOptionNames__Enum_SeekerFinalSpeed = 0x00000067,
        FloatOptionNames__Enum_MaxPingTime = 0x00000068,
        FloatOptionNames__Enum_CrewmateFlashlightSize = 0x00000069,
        FloatOptionNames__Enum_ImpostorFlashlightSize = 0x0000006a,
        FloatOptionNames__Enum_ShapeshifterCooldown = 0x000003e8,
        FloatOptionNames__Enum_ShapeshifterDuration = 0x000003e9,
        FloatOptionNames__Enum_ProtectionDurationSeconds = 0x0000044c,
        FloatOptionNames__Enum_GuardianAngelCooldown = 0x0000044d,
        FloatOptionNames__Enum_ScientistCooldown = 0x000004b0,
        FloatOptionNames__Enum_ScientistBatteryCharge = 0x000004b1,
        FloatOptionNames__Enum_EngineerCooldown = 0x00000514,
        FloatOptionNames__Enum_EngineerInVentMaxTime = 0x00000515,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class BoolOptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        VisualTasks = 0x00000001,
        GhostsDoTasks = 0x00000002,
        ConfirmImpostor = 0x00000003,
        AnonymousVotes = 0x00000004,
        IsDefaults = 0x00000005,
        UseFlashlight = 0x00000006,
        SeekerFinalVents = 0x00000007,
        SeekerFinalMap = 0x00000008,
        SeekerPings = 0x00000009,
        ShowCrewmateNames = 0x0000000a,
        ShapeshifterLeaveSkin = 0x000003e8,
        ImpostorsCanSeeProtect = 0x0000044c,
    };

#else
    enum BoolOptionNames__Enum {
        BoolOptionNames__Enum_Invalid = 0x00000000,
        BoolOptionNames__Enum_VisualTasks = 0x00000001,
        BoolOptionNames__Enum_GhostsDoTasks = 0x00000002,
        BoolOptionNames__Enum_ConfirmImpostor = 0x00000003,
        BoolOptionNames__Enum_AnonymousVotes = 0x00000004,
        BoolOptionNames__Enum_IsDefaults = 0x00000005,
        BoolOptionNames__Enum_UseFlashlight = 0x00000006,
        BoolOptionNames__Enum_SeekerFinalVents = 0x00000007,
        BoolOptionNames__Enum_SeekerFinalMap = 0x00000008,
        BoolOptionNames__Enum_SeekerPings = 0x00000009,
        BoolOptionNames__Enum_ShowCrewmateNames = 0x0000000a,
        BoolOptionNames__Enum_ShapeshifterLeaveSkin = 0x000003e8,
        BoolOptionNames__Enum_ImpostorsCanSeeProtect = 0x0000044c,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class Int32OptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        NumImpostors = 0x00000001,
        KillDistance = 0x00000002,
        NumEmergencyMeetings = 0x00000003,
        EmergencyCooldown = 0x00000004,
        DiscussionTime = 0x00000005,
        VotingTime = 0x00000006,
        MaxImpostors = 0x00000007,
        MinPlayers = 0x00000008,
        MaxPlayers = 0x00000009,
        NumCommonTasks = 0x0000000a,
        NumShortTasks = 0x0000000b,
        NumLongTasks = 0x0000000c,
        TaskBarMode = 0x0000000d,
        CrewmatesRemainingForVitals = 0x00000064,
        CrewmateVentUses = 0x00000065,
        ImpostorPlayerID = 0x00000066,
    };

#else
    enum Int32OptionNames__Enum {
        Int32OptionNames__Enum_Invalid = 0x00000000,
        Int32OptionNames__Enum_NumImpostors = 0x00000001,
        Int32OptionNames__Enum_KillDistance = 0x00000002,
        Int32OptionNames__Enum_NumEmergencyMeetings = 0x00000003,
        Int32OptionNames__Enum_EmergencyCooldown = 0x00000004,
        Int32OptionNames__Enum_DiscussionTime = 0x00000005,
        Int32OptionNames__Enum_VotingTime = 0x00000006,
        Int32OptionNames__Enum_MaxImpostors = 0x00000007,
        Int32OptionNames__Enum_MinPlayers = 0x00000008,
        Int32OptionNames__Enum_MaxPlayers = 0x00000009,
        Int32OptionNames__Enum_NumCommonTasks = 0x0000000a,
        Int32OptionNames__Enum_NumShortTasks = 0x0000000b,
        Int32OptionNames__Enum_NumLongTasks = 0x0000000c,
        Int32OptionNames__Enum_TaskBarMode = 0x0000000d,
        Int32OptionNames__Enum_CrewmatesRemainingForVitals = 0x00000064,
        Int32OptionNames__Enum_CrewmateVentUses = 0x00000065,
        Int32OptionNames__Enum_ImpostorPlayerID = 0x00000066,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class UInt32OptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        Keywords = 0x00000001,
    };

#else
    enum UInt32OptionNames__Enum {
        UInt32OptionNames__Enum_Invalid = 0x00000000,
        UInt32OptionNames__Enum_Keywords = 0x00000001,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class Int32ArrayOptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        MaxImpostors = 0x00000001,
        MinPlayers = 0x00000002,
    };

#else
    enum Int32ArrayOptionNames__Enum {
        Int32ArrayOptionNames__Enum_Invalid = 0x00000000,
        Int32ArrayOptionNames__Enum_MaxImpostors = 0x00000001,
        Int32ArrayOptionNames__Enum_MinPlayers = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class FloatArrayOptionNames__Enum : int32_t {
        Invalid = 0x00000000,
        KillDistances = 0x00000001,
    };

#else
    enum FloatArrayOptionNames__Enum {
        FloatArrayOptionNames__Enum_Invalid = 0x00000000,
        FloatArrayOptionNames__Enum_KillDistances = 0x00000001,
    };

#endif

    struct IGameOptions {
        struct IGameOptions__Class* klass;
        MonitorData* monitor;
    };

    struct IGameOptions__VTable {
        VirtualInvokeData get_Version;
        VirtualInvokeData get_GameMode;
        VirtualInvokeData get_MaxPlayers;
        VirtualInvokeData get_Keywords;
        VirtualInvokeData get_MapId;
        VirtualInvokeData get_NumImpostors;
        VirtualInvokeData get_TotalTaskCount;
        VirtualInvokeData get_IsDefaults;
        VirtualInvokeData get_RoleOptions;
        VirtualInvokeData AreInvalid;
        VirtualInvokeData SetRecommendations;
        VirtualInvokeData SetByte;
        VirtualInvokeData SetFloat;
        VirtualInvokeData SetBool;
        VirtualInvokeData SetInt;
        VirtualInvokeData SetUInt;
        VirtualInvokeData GetByte;
        VirtualInvokeData GetFloat;
        VirtualInvokeData GetBool;
        VirtualInvokeData GetInt;
        VirtualInvokeData GetIntArray;
        VirtualInvokeData GetFloatArray;
        VirtualInvokeData TryGetByte;
        VirtualInvokeData TryGetFloat;
        VirtualInvokeData TryGetBool;
        VirtualInvokeData TryGetInt;
        VirtualInvokeData TryGetIntArray;
        VirtualInvokeData TryGetFloatArray;
    };

    struct IGameOptions__StaticFields {
    };

    struct IGameOptions__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct IGameOptions__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct IGameOptions__VTable vtable;
    };

#pragma endregion


#pragma region List_1_GameData_PlayerInfo_
    struct __declspec(align(4)) List_1_GameData_PlayerInfo___Fields
    {
        struct GameData_PlayerInfo__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_GameData_PlayerInfo_
    {
        struct List_1_GameData_PlayerInfo___Class* klass;
        void* monitor;
        struct List_1_GameData_PlayerInfo___Fields fields;
    };

    struct GameData_PlayerInfo__Array {
        struct GameData_PlayerInfo__Array__Class* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct GameData_PlayerInfo* vector[32];
    };

    struct List_1_GameData_PlayerInfo___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_GameData_PlayerInfo___StaticFields
    {
        struct GameData_PlayerInfo__Array* _emptyArray;
    };

    struct List_1_GameData_PlayerInfo___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_GameData_PlayerInfo___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_GameData_PlayerInfo___VTable vtable;
    };
#pragma endregion

#pragma region RoleTypes__Enum__Array
    struct RoleTypes__Enum__Array
    {
        struct RoleTypes__Enum__Array__Class* klass;
        void* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        RoleTypes__Enum vector[32];
    };
    struct RoleTypes__Enum__Array__VTable
    {
    };

    struct RoleTypes__Enum__Array__StaticFields
    {
    };

    struct RoleTypes__Enum__Array__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct RoleTypes__Enum__Array__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct RoleTypes__Enum__Array__VTable vtable;
    };
#pragma endregion

#pragma region List_1_RoleTypes_
    struct __declspec(align(4)) List_1_AmongUs_GameOptions_RoleTypes___Fields {
        struct RoleTypes__Enum__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_AmongUs_GameOptions_RoleTypes_ {
        struct List_1_AmongUs_GameOptions_RoleTypes___Class* klass;
        MonitorData* monitor;
        struct List_1_AmongUs_GameOptions_RoleTypes___Fields fields;
    };

    struct List_1_AmongUs_GameOptions_RoleTypes___VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_Item;
        VirtualInvokeData set_Item;
        VirtualInvokeData IndexOf;
        VirtualInvokeData Insert;
        VirtualInvokeData RemoveAt;
        VirtualInvokeData get_Count;
        VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
        VirtualInvokeData Add;
        VirtualInvokeData Clear;
        VirtualInvokeData Contains;
        VirtualInvokeData CopyTo;
        VirtualInvokeData Remove;
        VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
        VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData System_Collections_IList_get_Item;
        VirtualInvokeData System_Collections_IList_set_Item;
        VirtualInvokeData System_Collections_IList_Add;
        VirtualInvokeData System_Collections_IList_Contains;
        VirtualInvokeData Clear_1;
        VirtualInvokeData System_Collections_IList_get_IsReadOnly;
        VirtualInvokeData System_Collections_IList_get_IsFixedSize;
        VirtualInvokeData System_Collections_IList_IndexOf;
        VirtualInvokeData System_Collections_IList_Insert;
        VirtualInvokeData System_Collections_IList_Remove;
        VirtualInvokeData RemoveAt_1;
        VirtualInvokeData System_Collections_ICollection_CopyTo;
        VirtualInvokeData get_Count_1;
        VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData get_Item_1;
        VirtualInvokeData get_Count_2;
    };

    struct List_1_AmongUs_GameOptions_RoleTypes___StaticFields {
        struct RoleTypes__Enum__Array* _emptyArray;
    };

    struct List_1_AmongUs_GameOptions_RoleTypes___Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct List_1_AmongUs_GameOptions_RoleTypes___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct List_1_AmongUs_GameOptions_RoleTypes___VTable vtable;
    };
#pragma endregion

#pragma region BinaryReader
    struct __declspec(align(4)) BinaryReader__Fields
    {
        void* m_stream;
        struct Byte__Array* m_buffer;
        void* m_decoder;
        void* m_charBytes;
        void* m_singleChar;
        void* m_charBuffer;
        int32_t m_maxCharsSize;
        bool m_2BytesPerChar;
        bool m_isMemoryStream;
        bool m_leaveOpen;
    };

    struct BinaryReader
    {
        struct BinaryReader__Class* klass;
        void* monitor;
        struct BinaryReader__Fields fields;
    };

    struct BinaryReader__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Dispose;
        VirtualInvokeData get_BaseStream;
        VirtualInvokeData Close;
        VirtualInvokeData Dispose_1;
        VirtualInvokeData Read;
        VirtualInvokeData ReadBoolean;
        VirtualInvokeData ReadByte;
        VirtualInvokeData ReadSByte;
        VirtualInvokeData ReadChar;
        VirtualInvokeData ReadInt16;
        VirtualInvokeData ReadUInt16;
        VirtualInvokeData ReadInt32;
        VirtualInvokeData ReadUInt32;
        VirtualInvokeData ReadInt64;
        VirtualInvokeData ReadUInt64;
        VirtualInvokeData ReadSingle;
        VirtualInvokeData ReadDouble;
        VirtualInvokeData ReadDecimal;
        VirtualInvokeData ReadString;
        VirtualInvokeData ReadChars;
        VirtualInvokeData Read_1;
        VirtualInvokeData ReadBytes;
        VirtualInvokeData FillBuffer;
    };

    struct BinaryReader__StaticFields
    {
    };

    struct BinaryReader__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct BinaryReader__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct BinaryReader__VTable vtable;
    };
#pragma endregion

#pragma region PlainDoor

    struct SomeKindaDoor__Fields
    {
        struct MonoBehaviour__Fields _;
    };

    struct PlainDoor__Fields {
        struct SomeKindaDoor__Fields _;
#if defined(_CPLUSPLUS_)
        SystemTypes__Enum Room;
#else
        uint8_t Room;
#endif
        int32_t Id;
        bool Open;
        void* myCollider;
        struct Collider2D* shadowCollider;
        void* animator;
        void* OpenDoorAnim;
        void* CloseDoorAnim;
        void* OpenSound;
        void* CloseSound;
        float size;
    };

    struct PlainDoor
    {
        struct PlainDoor__Class* klass;
        void* monitor;
        struct PlainDoor__Fields fields;
    };

    struct PlainDoor__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData SetDoorway;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData DoUpdate;
    };

    struct PlainDoor__StaticFields
    {
    };

    struct PlainDoor__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct PlainDoor__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct PlainDoor__VTable vtable;
    };
#pragma endregion

#pragma region AutoOpenDoor
    struct AutoOpenDoor__Fields
    {
        struct PlainDoor__Fields _;
        float ClosedTimer;
        float CooldownTimer;
    };

    struct AutoOpenDoor
    {
        struct AutoOpenDoor__Class* klass;
        void* monitor;
        struct AutoOpenDoor__Fields fields;
    };

    struct AutoOpenDoor__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData SetDoorway;
        VirtualInvokeData Serialize;
        VirtualInvokeData Deserialize;
        VirtualInvokeData DoUpdate;
    };

    struct AutoOpenDoor__StaticFields
    {
    };

    struct AutoOpenDoor__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct AutoOpenDoor__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct AutoOpenDoor__VTable vtable;
    };
#pragma endregion

#pragma region Vent
    struct Vent__Fields {
        struct MonoBehaviour__Fields _;
        int32_t Id;
        struct Vent* Left;
        struct Vent* Right;
        struct Vent* Center;
        void* Buttons;
        void* CleaningIndicators;
        void* EnterVentAnim;
        void* ExitVentAnim;
        struct Vector3 Offset;
        float spreadAmount;
        float spreadShift;
        struct SpriteRenderer* myRend;
    };

    struct Vent
    {
        struct Vent__Class* klass;
        void* monitor;
        struct Vent__Fields fields;
    };

    struct Vent__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_UsableDistance;
        VirtualInvokeData get_PercentCool;
        VirtualInvokeData get_UseIcon;
        VirtualInvokeData SetOutline;
        VirtualInvokeData CanUse;
        VirtualInvokeData Use;
    };

    struct Vent__StaticFields
    {
        struct Vent* currentVent;
    };

    struct Vent__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Vent__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Vent__VTable vtable;
    };
#pragma endregion

#pragma region StatsManager_Stats

    struct __declspec(align(4)) StatsManager_Stats__Fields {
        float banPoints;
        int64_t lastGameStarted;
        float FastestCrewmateWin_HideAndSeek;
        float FastestImpostorWin_HideAndSeek;
        void* gameplayStats;
        void* winReasons;
        void* loseReasons;
        void* drawReasons;
        void* mapWins;
        void* roleWins;
    };

    struct StatsManager_Stats {
        struct StatsManager_Stats__Class* klass;
        MonitorData* monitor;
        struct StatsManager_Stats__Fields fields;
    };

    struct StatsManager_Stats__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct StatsManager_Stats__StaticFields {
        void* SimpleStats;
    };

    struct StatsManager_Stats__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct StatsManager_Stats__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct StatsManager_Stats__VTable vtable;
    };

#pragma endregion

#pragma region StatsManager
    struct __declspec(align(4)) StatsManager__Fields
    {
        struct StatsManager_Stats* stats;
        bool loadedStats;
        void* logger;
    };

    struct StatsManager
    {
        struct StatsManager__Class* klass;
        void* monitor;
        struct StatsManager__Fields fields;
    };

    struct StatsManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData LoadStats;
        VirtualInvokeData SaveStats;
    };

    struct StatsManager__StaticFields
    {
        struct StatsManager* Instance;
    };

    struct StatsManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct StatsManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct StatsManager__VTable vtable;
    };
#pragma endregion

#pragma region NormalPlayerTask

#if defined(_CPLUSPLUS_)
    enum class NormalPlayerTask_TaskLength__Enum : int32_t {
        None = 0x00000000,
        Common = 0x00000001,
        Short = 0x00000002,
        Long = 0x00000003,
    };

#else
    enum NormalPlayerTask_TaskLength__Enum {
        NormalPlayerTask_TaskLength__Enum_None = 0x00000000,
        NormalPlayerTask_TaskLength__Enum_Common = 0x00000001,
        NormalPlayerTask_TaskLength__Enum_Short = 0x00000002,
        NormalPlayerTask_TaskLength__Enum_Long = 0x00000003,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class NormalPlayerTask_TimerState__Enum : int32_t
    {
        NotStarted = 0x00000000,
        Started = 0x00000001,
        Finished = 0x00000002,
    };

#else
    enum NormalPlayerTask_TimerState__Enum
    {
        NormalPlayerTask_TimerState__Enum_NotStarted = 0x00000000,
        NormalPlayerTask_TimerState__Enum_Started = 0x00000001,
        NormalPlayerTask_TimerState__Enum_Finished = 0x00000002,
    };

#endif

    struct NormalPlayerTask__Fields
    {
        struct PlayerTask__Fields _;
#if defined(_CPLUSPLUS_)
        NormalPlayerTask_TaskLength__Enum Length;
#else
        int32_t Length;
#endif
        int32_t taskStep;
        int32_t MaxStep;
        bool ShowTaskStep;
        bool ShowTaskTimer;
#if defined(_CPLUSPLUS_)
        NormalPlayerTask_TimerState__Enum TimerStarted;
#else
        int32_t TimerStarted;
#endif
        float TaskTimer;
        struct Byte__Array* Data;
        void* Arrow;
        bool arrowSuspended;
    };

    struct NormalPlayerTask
    {
        struct NormalPlayerTask__Class* klass;
        void* monitor;
        struct NormalPlayerTask__Fields fields;
    };

    struct NormalPlayerTask__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_TaskStep;
        VirtualInvokeData get_IsComplete;
        VirtualInvokeData Initialize;
        VirtualInvokeData OnRemove;
        VirtualInvokeData ValidConsole;
        VirtualInvokeData Complete;
        VirtualInvokeData AppendTaskText;
        VirtualInvokeData GetMinigamePrefab;
        VirtualInvokeData UpdateArrow;
        VirtualInvokeData FixedUpdate;
    };

    struct NormalPlayerTask__StaticFields
    {
    };

    struct NormalPlayerTask__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct NormalPlayerTask__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct NormalPlayerTask__VTable vtable;
    };
#pragma endregion

#pragma region Palette
    struct Palette {
        struct Palette__Class* klass;
        MonitorData* monitor;
    };

    struct Palette__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Palette__StaticFields {
        struct Color AcceptedGreen;
        struct Color DisabledGrey;
        struct Color DisabledClear;
        struct Color EnabledColor;
        struct Color Black;
        struct Color ClearWhite;
        struct Color HalfWhite;
        struct Color White_75Alpha;
        struct Color White;
        struct Color LightBlue;
        struct Color Blue;
        struct Color Orange;
        struct Color Purple;
        struct Color Brown;
        struct Color CrewmateBlue;
        struct Color ImpostorRed;
        struct Color CosmicubeCellUnlockedColor;
        struct Color CosmicubeCellLockedColor;
        struct Color CosmicubeQuality_NamePlate;
        struct Color CosmicubeQuality_Hat;
        struct Color CosmicubeQuality_Visor;
        struct Color CosmicubeQuality_Skin;
        struct Color CosmicubeQuality_Pet;
        struct Color CosmicubeQuality_Kill;
        struct Color InventorySelectedTextColor;
        struct Color InventoryTextColor;
        struct StringNames__Enum__Array* ColorNames;
        struct Color32__Array* PlayerColors;
        struct Color32__Array* ShadowColors;
        struct Color32 VisorColor;
    };

    struct Palette__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Palette__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Palette__VTable vtable;
    };
#pragma endregion

#pragma region SaveManager

#if defined(_CPLUSPLUS_)
    enum class ControlTypes__Enum : int32_t
    {
        VirtualJoystick = 0x00000000,
        ScreenJoystick = 0x00000001,
        Keyboard = 0x00000002,
        Controller = 0x00000003,
    };

#else
    enum ControlTypes__Enum
    {
        ControlTypes__Enum_VirtualJoystick = 0x00000000,
        ControlTypes__Enum_ScreenJoystick = 0x00000001,
        ControlTypes__Enum_Keyboard = 0x00000002,
        ControlTypes__Enum_Controller = 0x00000003,
    };

#endif

    struct Announcement
    {
        uint32_t Id;
        struct String* Text;
    };

    struct SaveManager {
        Il2CppClass* klass;
        MonitorData* monitor;
    };
#pragma endregion

#pragma region DestroyableSingleton_1_RoleManager_
    struct DestroyableSingleton_1_RoleManager___Fields
    {
        struct MonoBehaviour__Fields _;
        bool DontDestroy;
    };

    struct DestroyableSingleton_1_RoleManager_
    {
        struct DestroyableSingleton_1_RoleManager___Class* klass;
        void* monitor;
        struct DestroyableSingleton_1_RoleManager___Fields fields;
    };

    struct DestroyableSingleton_1_RoleManager___VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct DestroyableSingleton_1_RoleManager___StaticFields
    {
        struct RoleManager* _instance;
    };

    struct DestroyableSingleton_1_RoleManager___Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct DestroyableSingleton_1_RoleManager___StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct DestroyableSingleton_1_RoleManager___VTable vtable;
    };
#pragma endregion

#pragma region EngineerRole
    struct EngineerRole__Fields
    {
        struct RoleBehaviour__Fields _;
        struct Vent* currentTarget;
        float cooldownSecondsRemaining;
        float inVentTimeRemaining;
        float usesRemaining;
    };

    struct EngineerRole
    {
        struct EngineerRole__Class* klass;
        void* monitor;
        struct EngineerRole__Fields fields;
    };

    struct EngineerRole__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData get_IsDead;
        VirtualInvokeData get_IsAffectedByComms;
        VirtualInvokeData CanUse;
        VirtualInvokeData DidWin;
        VirtualInvokeData Deinitialize;
        VirtualInvokeData SpawnTaskHeader;
        VirtualInvokeData UseAbility;
        VirtualInvokeData OnMeetingStart;
        VirtualInvokeData OnVotingComplete;
        VirtualInvokeData Initialize;
        VirtualInvokeData SetUsableTarget;
        VirtualInvokeData SetPlayerTarget;
        VirtualInvokeData SetCooldown;
        VirtualInvokeData IsValidTarget;
        VirtualInvokeData FindClosestTarget;
        VirtualInvokeData GetAbilityDistance;
        VirtualInvokeData AdjustTasks;
        VirtualInvokeData AppendTaskHint;
    };

    struct EngineerRole__StaticFields
    {
    };

    struct EngineerRole__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct EngineerRole__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct EngineerRole__VTable vtable;
    };
#pragma endregion

#pragma region RoleManager
    struct RoleManager__Fields
    {
        struct DestroyableSingleton_1_RoleManager___Fields _;
        void* AllRoles;
        void* shapeshiftAnim;
        void* protectAnim;
        void* protectLoopAnim;
    };

    struct RoleManager
    {
        struct RoleManager__Class* klass;
        void* monitor;
        struct RoleManager__Fields fields;
    };

    struct RoleManager__VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct RoleManager__StaticFields
    {
        void* GhostRoles;
    };

    struct RoleManager__Class
    {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct RoleManager__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct RoleManager__VTable vtable;
    };

#pragma endregion

#pragma region AccountManager
#if defined(_CPLUSPLUS_)
    enum class KWSPermissionStatus__Enum : int32_t {
        Granted = 0x00000000,
        Rejected = 0x00000001,
        Pending = 0x00000002,
    };

#else
    enum KWSPermissionStatus__Enum {
        KWSPermissionStatus__Enum_Granted = 0x00000000,
        KWSPermissionStatus__Enum_Rejected = 0x00000001,
        KWSPermissionStatus__Enum_Pending = 0x00000002,
    };

#endif

#if defined(_CPLUSPLUS_)
    enum class EOSManager_AccountLoginStatus__Enum : int32_t {
        Offline = 0x00000000,
        LoggedIn = 0x00000001,
        WaitingForParent = 0x00000002,
        TempAccount = 0x00000003,
    };

#else
    enum EOSManager_AccountLoginStatus__Enum {
        EOSManager_AccountLoginStatus__Enum_Offline = 0x00000000,
        EOSManager_AccountLoginStatus__Enum_LoggedIn = 0x00000001,
        EOSManager_AccountLoginStatus__Enum_WaitingForParent = 0x00000002,
        EOSManager_AccountLoginStatus__Enum_TempAccount = 0x00000003,
    };

#endif

    struct DestroyableSingleton_1_AccountManager___Fields {
        struct MonoBehaviour__Fields _;
        bool DontDestroy;
    };

    struct AccountManager__Fields {
        struct DestroyableSingleton_1_AccountManager___Fields _;
        struct AccountTab* accountTab;
        void* enterGuardianEmailWindow;
        void* updateGuardianEmailWindow;
        void* guardianEmailConfirmWindow;
        void* genericInfoDisplayBox;
        void* enterDateOfBirthScreen;
        struct GameObject* waitingText;
        struct GameObject* postLoadWaiting;
        struct GameObject* privacyPolicyBg;
        void* signInScreen;
        void* PrivacyPolicy;
        void* chatModeMenuScreen;
#if defined(_CPLUSPLUS_)
        KWSPermissionStatus__Enum freeChatAllowed;
#else
        int32_t freeChatAllowed;
#endif
#if defined(_CPLUSPLUS_)
        KWSPermissionStatus__Enum customDisplayName;
#else
        int32_t customDisplayName;
#endif
#if defined(_CPLUSPLUS_)
        KWSPermissionStatus__Enum friendsListAllowed;
#else
        int32_t friendsListAllowed;
#endif
#if defined(_CPLUSPLUS_)
        KWSPermissionStatus__Enum accountLinkingAllowed;
#else
        int32_t accountLinkingAllowed;
#endif
        void* OnLoggedInStatusChange;
#if defined(_CPLUSPLUS_)
        EOSManager_AccountLoginStatus__Enum prevLoggedInStatus;
#else
        int32_t prevLoggedInStatus;
#endif
        struct TextMeshPro* accountDeletionText;
        bool isAccountWaitingForDeletion;
    };

    struct AccountManager {
        void* klass;
        MonitorData* monitor;
        struct AccountManager__Fields fields;
    };
#pragma endregion

#pragma region PlayerStorageManager
    struct DestroyableSingleton_1_PlayerStorageManager___Fields {
        struct MonoBehaviour__Fields _;
        bool DontDestroy;
    };

    struct PlayerStorageManager_CloudPlayerPrefs {
        struct String* ActivePodType;
        struct String* receiptRedemptionAccounts;
        uint32_t PlatformsLimitedItemsValidated;
        uint32_t IsAdult;
    };

#if defined(_CPLUSPLUS_)
    enum class UpdateState__Enum : int32_t {
        Connecting = 0x00000000,
        Failed = 0x00000001,
        Success = 0x00000002,
        PartialSuccess = 0x00000003,
    };

#else
    enum UpdateState__Enum {
        UpdateState__Enum_Connecting = 0x00000000,
        UpdateState__Enum_Failed = 0x00000001,
        UpdateState__Enum_Success = 0x00000002,
        UpdateState__Enum_PartialSuccess = 0x00000003,
    };

#endif

    struct PlayerStorageManager__Fields {
        struct DestroyableSingleton_1_PlayerStorageManager___Fields _;
        struct PlayerStorageManager_CloudPlayerPrefs _PlayerPrefs_k__BackingField;
#if defined(_CPLUSPLUS_)
        UpdateState__Enum _PlayerStorageLoadState_k__BackingField;
#else
        int32_t _PlayerStorageLoadState_k__BackingField;
#endif
        void* playerStorage;
        void* saveRoutine;
    };

    struct PlayerStorageManager {
        void* klass;
        MonitorData* monitor;
        struct PlayerStorageManager__Fields fields;
    };
#pragma endregion

#pragma region AchievementManager
    struct GameModes__Enum__Array {
        void* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        GameModes__Enum vector[32];
    };

    struct __declspec(align(4)) List_1_AmongUs_GameOptions_GameModes___Fields {
        struct GameModes__Enum__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_AmongUs_GameOptions_GameModes_ {
        void* klass;
        MonitorData* monitor;
        struct List_1_AmongUs_GameOptions_GameModes___Fields fields;
    };

    struct __declspec(align(4)) Dictionary_2_System_String_List_1_AmongUs_GameOptions_GameModes___Fields {
        struct Int32__Array* buckets;
        struct Dictionary_2_TKey_TValue_Entry_System_String_List_1_AmongUs_GameOptions_GameModes___Array* entries;
        int32_t count;
        int32_t version;
        int32_t freeList;
        int32_t freeCount;
        void* comparer;
        void* keys;
        void* values;
        struct Object* _syncRoot;
    };

    struct Dictionary_2_System_String_List_1_AmongUs_GameOptions_GameModes_ {
        void* klass;
        MonitorData* monitor;
        struct Dictionary_2_System_String_List_1_AmongUs_GameOptions_GameModes___Fields fields;
    };

    struct Dictionary_2_TKey_TValue_Entry_System_String_List_1_AmongUs_GameOptions_GameModes_ {
        int32_t hashCode;
        int32_t next;
        struct String* key;
        struct List_1_AmongUs_GameOptions_GameModes_* value;
    };

    struct Dictionary_2_TKey_TValue_Entry_System_String_List_1_AmongUs_GameOptions_GameModes___Array {
        void* klass;
        MonitorData* monitor;
        Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Dictionary_2_TKey_TValue_Entry_System_String_List_1_AmongUs_GameOptions_GameModes_ vector[32];
    };

    struct AchievementManager_1 {
        struct AchievementManager_1__Class* klass;
        MonitorData* monitor;
        //struct AchievementManager_1__Fields fields;
    };

    struct AchievementManager_1__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData Awake;
        VirtualInvokeData OnDestroy;
    };

    struct AchievementManager_1__StaticFields {
        struct Dictionary_2_System_String_List_1_AmongUs_GameOptions_GameModes_* AchievementGameModeKey;
        struct Dictionary_2_System_String_List_1_AmongUs_GameOptions_GameModes_* StatsGameModeKey;
    };

    struct AchievementManager_1__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct AchievementManager_1__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct AchievementManager_1__VTable vtable;
    };
#pragma endregion

    typedef Il2CppReflectionMethod MonoMethod;

    typedef Il2CppObject PlayerData;
    typedef Il2CppObject PlayerCustomizationData;
    typedef Il2CppObject PlayerPurchasesData;

    typedef Il2CppObject GameOptionsManager;
    typedef Il2CppObject GameManager;
    typedef Il2CppObject GameOptionsFactory;
}