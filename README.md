ILOAD $register valor   // Colocar o valor no registrador

LOAD $register $ram     // Colocar valor da ram no registrador 
STORE $register $ram    // Colocar valor do registrador na ram

ADD $register1 $register2 $register3 // register1 = register2 + register3
SUB $register1 $register2 $register3 // register1 = register2 - register3
MUL $register1 $register2 $register3 // register1 = register2 * register3
DIV $register1 $register2 $register3 // register1 = register2 / register3

LOOP valor
    //
    //
END

IF condicao
    //
    //
END

IF condicao
    //
    //
ELSE
    //
    //
END
