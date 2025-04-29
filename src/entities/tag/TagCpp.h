#ifndef TagCpp
#define TagCpp

enum TagCpp {
    // --- Special characters ---
    EOF = 65535,
    ERROR = 65534,

    // --- Operators ---
    GEQ = 1024,
    LEQ = 1025,
    EQ = 1026,
    AND = 1027,
    AND_EQ = 1028,
    XOR = 1029,
    XOR_EQ = 1030, 
    OR = 1031, 
    OR_EQ = 1032,
    NOT = 1033, 
    NOT_EQ = 1034,
    ARROW = 1035,
    INCREMENT = 1036,
    DECREMENT = 1037,
    LEFT_SHIFT = 1038,
    RIGHT_SHIFT = 1039,
    INC_ASSIGN = 1040,
    DEC_ASSIGN = 1041,
    MUL_ASSIGN = 1042,
    DIV_ASSIGN = 1043,
    MOD_ASSIGN = 1044,
    LSHIFT_ASSIGN = 1045,
    RSHIFT_ASSIGN = 1046,
    BITAND = 1047,
    BITOR = 1048,
    AND_BIT_ASSIGN = 1049,
    OR_BIT_ASSIGN = 1050,
    XOR_BIT_ASSIGN = 1051,
    COMPL = 1052,

    // --- Types ---
    SIGNED = 1124,
    UNSIGNED = 1125,
    LONG = 1126,
    SHORT = 1127,
    INT = 1128,
    FLOAT = 1129,
    DOUBLE = 1130,
    CHAR = 1131,
    CHAR8_t = 1132,
    CHAR16_t = 1133,
    CHAR32_t = 1134,
    WCHAR_T = 1135,
    AUTO = 1136,
    ENUM = 1137,
    VOID = 1138,
    BOOL = 1139,

    // --- Type Casting Operators ---
    STATIC_CAST = 1224,
    CONST_CAST = 1225,
    DYNAMIC_CAST = 1226,
    REINTERPRET_CAST  = 1227,

    // --- Literals ---
    TRUE = 1234,
    FALSE = 1235,
    NULLPTR = 1236,
    IDENTIFIER = 1337,
    STRING_LITERAL = 1338,

    // --- Control flow ---
    IF = 1324,
    ELSE = 1325,
    SWITCH = 1326,
    CASE = 1327,
    DEFAULT = 1328,
    FOR = 1329,
    WHILE = 1330,
    DO = 1331,
    BREAK = 1332,
    CONTINUE = 1333,
    GOTO = 1334,
    TRY = 1335,
    CATCH = 1336,
    THROW = 1337,
    RETURN = 1338,

    // --- Access modifiers ---
    PUBLIC = 1424, 
    PRIVATE  = 1425,
    PROTECTED = 1426,
    FRIEND = 1427,
    VIRTUAL = 1428,

    // --- Data structures ---
    SIZEOF = 1924,
    STRUCT = 1925,
    UNION = 1927,

    // --- Object handling ---
    USING = 2024,
    NAMESPACE = 2025,
    CLASS = 2026,
    CONCEPT = 2027,
    TYPENAME = 2028,
    TEMPLATE = 2029,
    THIS = 2030,
    FINAL = 2031,
    OVERRIDE = 2032,

    // --- Function control ---
    EXPLICIT = 2124,
    NOEXCEPT = 2125,
    OPERATOR = 2126,
    REQUIRES = 2127,
    NEW = 2128,
    DELETE = 2129,

    // --- Meta-programming ---
    DECLTYPE = 2224,
    REFLEXPR = 2225,
    STATIC_ASSERT = 2226,

    // --- Package and Import Management ---
    IMPORT = 2324,
    EXPORT = 2325,
    MODULE = 2326,

    // --- Transaction Memory ---
    ATOMIC_CANCEL = 2424,
    ATOMIC_COMMIT = 2425,
    ATOMIC_NOEXCEPT = 2426,
    TRANSACTION_SAFE = 2427,
    TRANSACTION_SAFE_DYNAMIC = 2428, 

    // --- Contracts ---
    CONTRACT_ASSERT = 2524,
    PRE = 2525,
    POST = 2526,
    TRIVIALLY_RELOCATABLE_IF_ELIGIBLE = 2527,
    REPLACEABLE_IF_ELIGIBLE = 2528,

    // --- Coroutine support ---
    CO_RETURN = 2624,
    CO_AWAIT = 2625,
    CO_YIELD = 2626,

    // --- Storage classes ---
    ASM = 2724,
    CONST = 2725,
    CONSTEXPR = 2726,
    CONSTEVAL = 2727,
    CONSTINIT = 2728,
    MUTABLE = 2729,
    STATIC = 2730,
    INLINE = 2731,
    REGISTER = 2732,
    TYPEDEF = 2733,
    EXTERN = 2734,
    THREAD_LOCAL = 2735,
    SYNCHRONIZED = 2736,
    VOLATILE = 2737,

    // --- Type information ---
    TYPEID = 2824,

    // --- Preprocessor ---
    _PRAGMA = 2924

    // --- Alignment ---
    ALIGNAS = 1824,
    ALIGNOF = 1825,
};

#endif // TagCpp
 