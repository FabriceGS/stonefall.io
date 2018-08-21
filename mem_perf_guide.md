
# Memory Management & Performance Guide
A guide for easily navigating some of the confusing C++ semanctics
we'll use in the this project.

## Basic Definitions:
(Pre C++17)
An lvalue is an expresssion that persists in scope, and has meaning on its own. These are denoted
lvalues, because they can exist on the left side of an assignment expression. 
(lvalue reference &)

An rvalue is a temporary expression that does not persist beyond the expression that uses it.
These are called rvalues, because they can only exist on the right side of an assignment expression.
(rvalue reference &&)

(C++17 Onward)
A glvalue is an expression whose evaluation determines the identity of an object, 
bit-field, or function.

An lvalue has an address that your program can access. Examples of lvalue expressions include 
variable names, including const variables, array elements, function calls that return an 
lvalue reference, bit-fields, unions, and class members.

A prvalue expression has no address that is accessible by your program. Examples of prvalue 
expressions include literals, function calls that return a non-reference type, and temporary 
objects that are created during expression evalution but accessible only by the compiler.

An xvalue expression has an address that no longer accessible by your program but can be used 
to initialize an rvalue reference, which provides access to the expression. Examples include 
function calls that return an rvalue reference, and the array subscript, member and pointer to 
member expressions where the array or object is an rvalue reference.

An rvalue is a prvalue or an xvalue.

## Lvalue References:
Basically syntatic sugar for a pointer, but behaves syntactically like an object. A reference 
cannot be changed after initialization. Denoted with &

## Rvalue References:
Same concept as lvalue references, but support move semantics and perfect forwarding. Denoted with &&

## Move Semantics (IMPORTANT):
Move semantics allow code to transfer resources from one object to another. This is faster than
copying from one object to another, which assignment operators (=) do under the hood. Moving
resources from one object to another with std::move() leaves the source object undefined.

## Perfect Forwarding:
Lengthy, complicated and unnecessary so far. But read if you please.
https://docs.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp

## Constructor Parameters (IMPORTANT):
If you want to pass an object to another objects constructor with the intent for that object to
modify your passed object, take the object by reference or by (smart)pointer.

If you want to pass an object to another object with NO INTENT TO USE THE PASSED OBJECT AGAIN
you should convert it to an rvalue (with std::move) and pass it into the constructor. Furthermore, 
if the constructor is only setting a member variable, std::move the object from the constructor
argument to the member variable.

## Function Parameters (IMPORTANT):
If you want to pass an object to a function to get modified, pass it by reference or by (smart)pointer.

If you want to pass an object to another function with NO INTENT TO USE THE PASSED OBJECT AGAIN
you should convert it to an rvalue (with std::move) and pass it into the function.

## Both (IMPORTANT):
If you want to pass an object to another object/function and use it again, pass it by 
const & or by value, depending on:
- If the passed object is not going to be copied within the function/constructor pass by const&.
- If the passed object will be copied within the function/constructor, pass by value and std::move
  from the constructor arg to the copy. If more copies are necessary, copy from that copy.

Finally, the same rules for objects apply to smart pointers as they are expensive. Also,
please refrain from sending regular pointers representing objects through functions. I understand
the need in Websockets as they represent bits/json streams, but limit them elsewhere.

## SUBJECT TO EDITS!!