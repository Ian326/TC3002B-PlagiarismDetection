#ifndef TagC
#define TagC

enum TagC {
    // --- Special Characters ---
    EOF = 65535,
    ERROR = 65534,

    // --- Operators ---
    EQ = 1024,
    GEQ = 1025,  
    LEQ = 1026,
    NEQ = 1027,
    ARROW = 1028,
    INCREMENT = 1029,
    DECREMENT = 1030,
    LEFT_SHIFT = 1031,
    RIGHT_SHIFT = 1032,
    INC_ASSIGN = 1033,
    DEC_ASSIGN = 1034,
    MUL_ASSIGN = 1035,
    DIV_ASSIGN = 1036,
    MOD_ASSIGN = 1037,
    LSHIFT_ASSIGN = 1038,
    RSHIFT_ASSIGN = 1039,
    AND_BIT_ASSIGN = 1040,
    OR_BIT_ASSIGN = 1041,
    XOR_BIT_ASSIGN = 1042,
    AND = 1043,
    OR = 1044,

    // --- Types ---
    SIGNED = 1124,
    UNSIGNED = 1125,
    LONG = 1126,
    SHORT = 1127,
    INT = 1128,
    FLOAT = 1129,
    DOUBLE = 1130,
    CHAR = 1131,
    AUTO = 1132,
    ENUM = 1133,  
    VOID = 1134, 
    BOOL = 1135,
    COMPLEX = 1136,
    IMAGINARY = 1137,
    BITINT = 1138,
    DECIMAL32 = 1139,
    DECIMAL64 = 1140,
    DECIMAL128 = 1141,

    // --- Literals ---
    TRUE = 1224,
    FALSE = 1225,
    NULLPTR = 1226,
    IDENTIFIER = 1227,
    STRING_LITERAL = 1228,

    // --- Control Flow ---
    IF = 1324,
    ELIF = 1325,
    ELSE = 1326,
    SWITCH = 1327,
    CASE = 1328,
    DEFAULT = 1329,
    FOR = 1330,
    WHILE = 1331,
    DO = 1332,
    BREAK = 1333,
    CONTINUE = 1334,
    GOTO = 1335,
    RETURN = 1336,

    // --- Data Structures ---
    TYPEOF = 1524,
    SIZEOF = 1525,
    STRUCT = 1526,
    UNION = 1527,
    TYPEDEF = 1624,
    TYPEOF_UNQUAL = 1625,

    // --- Storage Class Specifiers ---
    CONST = 1724,
    CONSTEXPR = 1725,
    EXTERN = 1726,
    INLINE = 1727,
    REGISTER = 1728,
    RESTRICT = 1729,
    NORETURN = 1730,
    THREAD_LOCAL = 1731, 
    STATIC = 1732, 
    VOLATILE = 1733,
    STATIC_ASSERT = 1734,

    // --- Package and Import Management ---
    INCLUDE = 1824,

    // --- Miscellaneous ---
    ATOMIC = 1924,
    GENERIC = 1925

    // --- Alignment ---
    ALIGNAS = 1424,
    ALIGNOF = 1425,
};

#endif // TagC
