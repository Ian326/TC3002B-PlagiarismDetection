#ifndef TagJava
#define TagJava

enum TagJava {
    // --- Special characters ---
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
    UNSIGNED_RSHIFT = 1033,
    INC_ASSIGN = 1034,
    DEC_ASSIGN = 1035,
    MUL_ASSIGN = 1036,
    DIV_ASSIGN = 1037,
    MOD_ASSIGN = 1038,
    LSHIFT_ASSIGN = 1039,
    RSHIFT_ASSIGN = 1040,
    UNSIGNED_RSHIFT_ASSIGN = 1041,
    AND_BIT_ASSIGN = 1042,
    OR_BIT_ASSIGN = 1043,
    XOR_BIT_ASSIGN = 1044,
    INSTANCEOF = 1045,
    AND = 1046,
    OR = 1047,

    // --- Types ---
    BOOLEAN = 1124,
    BYTE = 1125,
    CHAR = 1126,
    SHORT = 1127,
    INT = 1128,
    LONG = 1129,
    FLOAT = 1130,
    DOUBLE = 1131,
    VOID = 1132,

    // --- Literals ---
    TRUE = 1224,
    FALSE = 1225,
    NULL = 1226,

    // --- Control Flow ---
    IF = 1324,
    ELSE = 1325,
    SWITCH = 1326,
    CASE = 1327,
    DEFAULT = 1328,
    DO = 1329,
    WHILE = 1330,
    FOR = 1331,
    BREAK = 1332,
    CONTINUE = 1333,
    RETURN = 1334,
    TRY = 1335,
    CATCH = 1336,
    FINALLY = 1337,
    THROW = 1338,
    THROWS = 1339,
    ASSERT = 1340,

    // --- Class Declarations ---
    CLASS = 1424,
    INTERFACE = 1425,
    EXTENDS = 1426,
    IMPLEMENTS = 1427,
    ENUM = 1428,
    ABSTRACT = 1429,
    FINAL = 1430,
    STRICTFP = 1431,
    NATIVE = 1432,
    SYNCHRONIZED = 1433,
    TRANSIENT = 1434,
    VOLATILE = 1435,

    // Storage Classes
    STATIC = 1824

    // --- Object and Memory Operations ---
    NEW = 1524,
    THIS = 1525,
    SUPER = 1526,
      
    // --- Access Modifiers ---
    PRIVATE = 1624,
    PROTECTED = 1625,
    PUBLIC = 1626,

    // --- Package and Import Management ---
    PACKAGE = 1724,
    IMPORT = 1725,
};

#endif // TagJava
