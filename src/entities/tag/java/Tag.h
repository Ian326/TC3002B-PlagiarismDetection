#ifndef JAVA_TAG_H
#define JAVA_TAG_H

namespace Java {
    enum Tag {
        // --- Special characters ---
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
        NULLPTR = 1226,
    
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
    
        // --- Package and Import Management ---
        PACKAGE = 1424,
        IMPORT = 1425,
    
        // Storage Class Specifiers
        STATIC = 1524,
    
        // --- Class Declarations ---
        CLASS = 1624,
        INTERFACE = 1625,
        EXTENDS = 1626,
        IMPLEMENTS = 1627,
        ENUM = 1628,
        ABSTRACT = 1629,
        FINAL = 1630,
        STRICTFP = 1631,
        NATIVE = 1632,
        SYNCHRONIZED = 1633,
        TRANSIENT = 1634,
        VOLATILE = 1635,
    
        // --- Object and Memory Operations ---
        NEW = 1724,
        THIS = 1725,
        SUPER = 1726,
          
        // --- Access Modifiers ---
        PRIVATE = 1824,
        PROTECTED = 1825,
        PUBLIC = 1826
    };
} // namespace Java

#endif // JAVA_TAG_H
