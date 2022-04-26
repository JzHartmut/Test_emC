
 typedef float MT_myOperation(float argument);

 typedef float (*MT_myOperation_B)(float argument);


 MT_myOperation* pointer_to_operation;

 MT_myOperation_B pointer_to_B;

 //Example for an operation:
 float myOperationXyz ( float arg) {
   return 2.3f * arg; 
 }



 void test_fnPointer() {
 
   pointer_to_operation = &myOperationXyz;

   void* voidX = (void*)pointer_to_operation;


   pointer_to_B = myOperationXyz;

   float result = pointer_to_operation(3.14f);

   result = pointer_to_B(4.5f);

   //cast test:
   void* void_a = (void*)pointer_to_operation;
   MT_myOperation* pointer_to_A2 = (MT_myOperation*) void_a; 

   //cast test with second variant, works, but it is worse to understand
   //because it is not obviously, that MT_myOperation_B is a pointer type.
   void* void_B = (void*)pointer_to_B;
   MT_myOperation_B pointer_to_B2 = (MT_myOperation_B) void_B;

 
 }