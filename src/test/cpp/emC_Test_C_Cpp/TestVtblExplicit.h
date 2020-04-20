#ifndef HEADERGUARD_TestVtblExplicit
#define HEADERGUARD_TestVtblExplicit


//It is an interface, only define operations, without implementation.

class IfcCvirt {
  public: virtual void doFirst ( float val )=0;
  public: virtual void doOther ( float val )=0;
  public: virtual void doAny ( int val1, int val2 )=0;
}; 

//It is one from more implementation classes:

class ImplAvirt : public IfcCvirt { 
  protected: int i1, i2; float f1;  //any data

  public: virtual void doFirst ( float val );
  public: void doOther ( float val );
  public: void doAny ( int val1, int val2 );
  public: virtual char const* doAnywhat();
};

//The `doFirst` can be overridden again, a new doAnywhat has an implementation, 
//  but can be overridden in an derived class.   

//A further inheritance overrides both operations and stops ability to override `doFirst`:

class ImplBvirt : public ImplAvirt { 
  public: void doFirst ( float val );
  public: virtual char const* doAnywhat();
};

void testVtbl_virtual ( IfcCvirt* ifc);







/**********************************************************************************************************/
/* Definition without the automatic virtual table, 'be explicit' ******************************************/

/**Firstly we need C-FunctionType-Prototypes. 
 * Note: the typedef is syntactically more clear than (*Oper_doit...)
 */
typedef void Oper_doitFloat_IfcExpl(class IfcExpl* thiz, float val);
typedef void Oper_doitInt2_IfcExpl(class IfcExpl* thiz,  int val1, int val2);

//Experience for C++ function pointers:
typedef void Oper_doit(float val);

#define sign_Vtbl_IfcExpl "sign_Vtbl_IfcExpl_MyAppl"

struct Vtbl_IfcExpl_T;

/**This class is used as interface reference, without implememtation. 
 * It has only a protected ctor, cannot instantiate.
 */
class IfcExpl {
  /**The IfcExpl has not virtual operations, 
   * but the explicit reference to the vtbl. */
  public: struct Vtbl_IfcExpl_T const* const vtbl_IfcExpl;
  /**An explicit ctor is necessary: */
  protected: IfcExpl ( struct Vtbl_IfcExpl_T const* const);
  //It is only an experience with C++-FunctionPointer:
  public: void doit_dontUse(float val); 
};

/**This is the explicitely virtual table of the interface. 
 * Its content is adequate the vtbl internally in C++
 * if virtual operations are defined.*/ 
typedef struct Vtbl_IfcExpl_T {
  char const* sign;
  Oper_doitFloat_IfcExpl* doFirst;
  Oper_doitFloat_IfcExpl* doOther;
  Oper_doitInt2_IfcExpl* doAny;
  //this is only useable to assign adequate operations of IfcExpl, not for derivation.
  //left empty in this test! (null), do not use!!
  Oper_doit IfcExpl::* doit2;  
} Vtbl_IfcExpl_s;





/*****************************************************************************************/
/* Definition of a derive-able C++ class with its explitit vtbl  */



typedef char const* Oper_doAnywhat(class ImplA* thiz);

#define sign_Vtbl_ImplA "sign_Vtbl_ImplA_MyAppl"

/**The explicitely virtual table of the class ImplA.
 * Its content is adequate the vtbl internally in C++
 * if virtual operations are defined.*/ 
typedef struct Vtbl_ImplA_T {
  char const* sign;
  //All own overrideable operations should be contained here.
  Oper_doitFloat_IfcExpl* doFirst;
  Oper_doAnywhat* doAnywhat;

  /* It contains the interface vtbl. 
   * If there are more interfaces, more inner vtbl are necessary. */
  Vtbl_IfcExpl_s IfcExpl;
} Vtbl_ImplA_s;






class DataClass {
};

class ImplA : public IfcExpl, protected DataClass {
  protected: Vtbl_ImplA_s const* const vtbl_ImplA;
  protected: int i1, i2; float f;
  public: ImplA ( );
  protected: ImplA ( Vtbl_ImplA_s const* vtblA);
  /**Defines the implementation of the interface-operations.
   * The identifier do not need identically, but it is strongly recommended. */
  public: void doFirst ( float val);
  public: void doOther ( float val);
  public: void doAny ( int val1, int val2);
  public: float getVal ( ){ return this->f; } 
};




/*****************************************************************************************/
/* Definition of a deriving C++ class with its explitit vtbl  */

#define sign_Vtbl_ImplB "sign_Vtbl_ImplB_MyAppl"


typedef struct Vtbl_ImplB_T {
  char const* sign_ImplB;
  Oper_doAnywhat* doAnywhat;
  Vtbl_ImplA_s ImplA;
} Vtbl_ImplB_s;


class ImplB : public ImplA {
  Vtbl_ImplB_s const* const vtbl_ImplB;
  //because it contains only overriding operations, no more data.
  public: ImplB ( );
  public: void doFirst ( float val ); //other overriding implementation
  public: char const* doAnywhat ( );  //other overriding implementation
};






/*****************************************************************************************/
/* Definition of another deriving C++ class for IfcExpl with its explitit vtbl  */

class ImplA2 : public IfcExpl, protected DataClass {
  protected: int i1, i2; float f;
  public: ImplA2 ( );
          /**Defines the implementation of the interface-operations.
          * The identifier do not need identically, but it is strongly recommended. */
  public: void doFirst ( float val);
  public: void doOther ( float val);
  public: void doAny ( int val1, int val2);
  public: float getVal ( ){ return this->f; } 
};












void test_TestVtblExplicit ( );


#endif //HEADERGUARD_TestVtblExplicit
