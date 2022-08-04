// Code your testbench here
 //IMPORT FUNCTION DPI DECLARATION FROM C
import "DPI-C" function int py_func(int x);    

module sv_top;
  initial begin
    void'(py_func(5));
    void'(py_func(15));
    void'(py_func(52));
    void'(py_func(56));
    void'(py_func(75));
  end
endmodule