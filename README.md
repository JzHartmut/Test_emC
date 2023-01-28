# This git Archive contains test Sources for emC

## emC

This is a comprehensive test and example environment of src_emC

Refer to webpage [https://vishia.org/emc/index.html]

Especially work with this git archives refer to [https://vishia.org/emc/html/TestOrg/testStrategie_en.html] 

emC is embedded multiplatform C. The approach:

* C and C++ are platform-independent languages from view of the algorithm.
* A user application can run on PC for test and simulation as well as on several platforms.
* The adaption to operation system access is done by the OSAL layer (Operation System Adaption)
* This OSAL is not a hard standard, it is flexible for your application,
  but some common approaches are regarded.
* The adaption to hardware access should be done by user by adequate wrapper routines, 
  whereby the calculation time is not ineffective if inline keyword is used.
* The language style and standards should be a intersection (subset) of all common possibilities,
  this subset is enough productive. Do not use special featuers which has not really an advantage.
* Use an ObjectOriented approach! It is possible in C too.
* Combine C and C++ in a well kind. Define pure data primary in C with typedef struct
  and integrate that via inheritance in C++ classes for C++ usage.
* Keep core algorithm in C if it is conceivable that C is need for a target platform;
  use C++ for more complex software structures which do never run on simple C only targets.
  Whereby call the C core routines with a simple C++ wrapping. C++ is usually better readable.
* ObjectJc: The origin of this set of sources had been a Runtime system for Java-translated
  C-codes. Java has a well infrastructure with a common base class java.lang.Object, 
  a reflection system for type test and symbolic access and some more.
  This approach is able to use for C/C++ too. The core access to this approach
  is the struct ObjectJc.


