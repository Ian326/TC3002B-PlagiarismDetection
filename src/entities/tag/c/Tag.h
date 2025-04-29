#ifndef C_TAG_H
#define C_TAG_H

namespace C {
    enum Tag {
        // --- Special Characters ---
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
        ATOMIC = 1924,
        GENERIC = 1925,
    
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
    
        // --- Package and Import Management ---
        INCLUDE = 1424,
    
        // --- Storage Class Specifiers ---
        CONST = 1524,
        CONSTEXPR = 1525,
        EXTERN = 1526,
        INLINE = 1527,
        REGISTER = 1528,
        RESTRICT = 1529,
        NORETURN = 1530,
        THREAD_LOCAL = 1531, 
        STATIC = 1532, 
        VOLATILE = 1533,
        STATIC_ASSERT = 1534,
    
        // --- Data Structures ---
        TYPEOF = 1624,
        SIZEOF = 1625,
        STRUCT = 1626,
        UNION = 1627,
        TYPEDEF = 1628,
        TYPEOF_UNQUAL = 1628,
    
        // --- Alignment ---
        ALIGNAS = 1724,
        ALIGNOF = 1725
    };
} // namespace C

#endif // C_TAG_H
