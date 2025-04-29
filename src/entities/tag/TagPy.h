#ifndef TagPy
#define TagPy

enum TagPy
{
    // --- Special characters ---
    EOF = 65535,
    ERROR = 65534,

    // --- Operators ---
    EQ = 1024, 
    GEQ = 1025,
    LEQ = 1026,
    NEQ = 1027,
    ARROW = 1028,
    EXP = 1029,
    ROUND_DIV = 1030,
    LEFT_SHIFT = 1031,
    RIGHT_SHIFT = 1032,
    WALRUS = 1033,
    INC_ASSIGN = 1034,
    DEC_ASSIGN = 1035,
    MUL_ASSIGN = 1036,
    DIV_ASSIGN = 1037,
    ROUND_DIV_ASSIGN = 1038,
    MOD_ASSIGN = 1039,
    MAT_MUL_ASSIGN = 1040,
    LSHIFT_ASSIGN = 1041,
    RSHIFT_ASSIGN = 1042,
    AND_BIT_ASSIGN = 1043,
    OR_BIT_ASSIGN = 1044,
    XOR_BIT_ASSIGN = 1045,
    EXP_ASSIGN = 1046,
    AND = 1047,
    OR = 1048,
    NOT = 1049,

    // --- Types ---
    INT = 1124,
    FLOAT = 1125,
    COMPLEX = 1126,
    BOOL = 1127,
    STR = 1128,
    BYTES = 1129,
    LIST = 1130,
    TUPLE = 1131,
    SET = 1132,
    DICT = 1133,
    NONE = 1134,

    // --- Literals ---
    TRUE = 1224,
    FALSE = 1225,
    IDENTIFIER = 1226,
    STRING_LITERAL = 1127,

    // --- Control Flow ---
    IF = 1324,
    ELIF = 1325,
    ELSE = 1326,
    FOR = 1324,
    WHILE = 1325,
    BREAK = 1326,
    CONTINUE = 1327,
    TRY = 1324,
    EXCEPT = 1325,
    FINALLY = 1326,
    RAISE = 1327,
    ASSERT = 1328,

    // --- Identity operators ---
    IN = 1424,
    IS = 1425,

    // --- Functions and classes ---
    DEF = 1524,
    RETURN = 1525,
    LAMBDA = 1526,
    CLASS = 1527,

    // --- Context management ---
    WITH = 1624,
    AS = 1625,

    // --- Package and Import Management ---
    IMPORT = 1724,
    FROM = 1725,

    // --- Miscellaneous ---
    PASS = 1824,
    DEL = 1825,
    GLOBAL = 1826,
    NONLOCAL = 1827,
    YIELD = 1828,
    AWAIT = 1829,
    ASYNC = 1830
};

#endif // TagPy