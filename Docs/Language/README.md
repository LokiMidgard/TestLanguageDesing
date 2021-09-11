# Types

Types define the shape of an object. Every thing has an acociated type
that descripe the data the thing has and the operations that can be performed.
However not for every Type there exists a Thing.

A Type can be a subtype of another. Having all the Propertys and Mthods of the base type.
Every Type is a subtype of either Object or void. The null Type is a subtype of void. 
No instance of a void type can ever exist.

A Type may be constructed of other Types by intersecting (`&`) or union (`|`) the type.
The most common is propably the union of null and another type. Intersecting a Type
means that the object that satisfies it has everything those intersected types have it is both types.
Union means it is at least one of those types.

A Type can be defined by explicitly describing the members

```typescript
type NAME {
	//...Members
}
```

You can also define a Type over other types

```typescript
type NAME = OtherType
```

In this case OtherType CAN be assigned to NAME.

```typescript
explicite type NAME = OtherType
```
In this case OtherType CAN NOT be assigned to NAME (without casting). The other way always works.

## Restrictions

You can restrict a value of a Type for some types further. 

For number types you can use `<` `<=` `>` `>=`

```typescript
int > 5 and < 10 // will be a value between 5 and 10 (exclusive)
int < 5 or > 10 // will be a value less then 5 or higher then 10
int > 0        // will be a positive value
```

For every other type that has compile time constants you can use `oneof`

```typescript
string oneof "Hallo" "Welt"
string | int oneof "Hallo" 3
```
You can shorten this like this
```typescript
"Hallo" | "Welt"
"Hallo" | 3
```

## Template

A Type may have parameter to get different behaviors of one type. An example is a list of `T`.
If you need a list of `int` you can set `T` to `int`, if you need `string` you can set it to `string` 

Templates are defined in brackets `<` `>` after the type name.

```typescript
type List<T> {
	//...
}
```
Would define a type Named list that can be parametrized with another type `T`.

```typescript
type List<size:int> {
	//...
}
```
You can also add a Type after a parameter seperated by a collon (`:`) to define that not a Type
should be used but an instance of that type. In the case above this could be the number of elements
in the list. You can alsow write `T:Type` which is identical to just `T`.

```typescript
type List<T, size:int> {
	//...
}
```
Multiple Parameter can be seperated with a comma (`,`).

```typescript
type List<T, size:int > 0> {
	//...
}
```

You can also restrict the type.


## Aliases

A Type may have defined one or more aliase. An Alias is an alternative namen that replaces the 
original name of the Type. Normaly used for localisation.

To Define an Alias

```typescript
alias AliasName OldName NewName

// e.g.

alias de String Text

```
To activate an alias either enable it using the alias name as a flag for the compile/interperter or
write a compiler directive in the source code.
```typescript
## AliasName
```
After that line the alias is enabled untill the end of the file or untill the alias is revoked using
```typescript
#! AliasName
```

An AliasName is not unique you can define as many alias as you want with the same name.
You can not define more than one alias for the same Type with the same AliasName.
If you defined that `String` should be `foo` you can't define that it should be `ba` unless both
alias definitions have a different AliasName.

Types may have a default Alias provided that can localy be overridden.

## Standard Types

Following standard types are provided

* String
* int
* float
* Array<T>


# variables

A variable can hold an object of a specific type. The type is either explicitly defined
or automaticly detected.

```typescript
var foo = 3 // will be int
```

Restrictions will not be automaticly enforced. If you need a restriction you need to define the type explicitly.

```typescript
var foo : int >3 = 3;
```

If the type is explicitly defined an assignment need not to be done when declaring the variable.

```typescript
var foo : int;
```



Restrictions of a variable will be applied dynamicly and staticly.
When a restriciton is explicitly defined (staticly) no assignment may violate it.

Dynamicly restrictions will be applied for every line.

```typescript
var foo: int > 0  = 4 
// foo explicitly >0
// foo implicitly 4

foo  = foo - 3
// foo explicitly >0
// foo implicitly 1

foo  = foo - 3 // error foo is implicitly 1 substracted by 3 would be less then 0
```

# Object creation

## Text
String can be created by writing the text between one or more `"`.

```typescript
var foo = "Hallo Welt"; // single double quote
var foo = ""Hallo "Die" Welt""; // double double quote allows using single double quote in the text
var foo = "Multi 
line text
" // Multiline is also possible

var foo = """"""Hello World""""""; // you can use as many " as you want.
```

You can interpolate strings using `{` `}`. You need the same number of brackates as double quotes.

```typescript
var foo = ""Hello {{3}} World"" // Prints Hello 3 World
var foo = ""Hello {3} World"" // Prints Hello {3} World
```

Prepending the double quotes with an `@` will ignore the leading whitespaces of a text.
In a multi line text where the first line is empty, every line will cut the first `x` whitespaces
where `x` is the number of whitespaces in the first line with no whitespaces.

```typescript
var foo = @"" "Hello World"""; //Prints "Helo World"

var foo = @"
	Multi line text
	This line is not indented
	  This line is indeted by 2
" // multiline with leading whitespaces
```
## Single Character

A single character is prepended by `\`

```typescript
var foo = \c; // will store the character c in the variable
```

# Numbers

You write numbers by writing the number in the source code.
```typescript
var foo = 3; // stores the int 3.
```

You can use underscores to seperate the digits of a number
```typescript
var foo = 3_0000; // stores the int 3000.
```

You can prepand the number if `0xb` where `x` is the base. `02b10` would be 2 in
binary encoding. You can also write `0x` as a short version for hexadecimal
`016b`.

You can append a letter at the end do define the type of the number

letter|type
i|int
l|long
f|float
df|double
d|decimal
b|byte
s|short

you can also prepend the type leter with u to make it unsigned `ul` for unsigned
long. The unsigned modifier is not valid for every type.

# custom types

every other (not composed) type can be instanciated using the `new` keyword.

```typescript
var foo = new bar();
```

An object that was created this way needs to be explicitly deleted when no
longer needed.

```typescript
delete foo;
```

Only the variable owning the object may delete. When an object is created the
variable it is assigned to is the owner

```typescript
var foo = new object();
var bar = foo; // also points to the object created
delete bar; // error bar does not own the object.
```

After an object is deleted it can no longer be accesed. If you know that the
object is deleted, or do not know if it is still valid you need to check first
if it is still valid

```typescript
var foo = new object();
var bar = foo; // also points to the object created
delete foo; 
bar.something() // error object was deleted
```
```typescript
var foo = // get object from somewhere;
foo.something() // error state of object unkonw
```
```typescript
var foo = // get object from somewhere;
if(foo is not deleted)
	foo.something() // this is ok
else
	foo.something() // this is NOT
```

You must to delete an object before its owning variable goes out of scope. You
can alos transfare the ownership of an object to another variable.

```typescript
var foo = new object();
var bar = own foo; 
delete bar;  // this works since bar now owns the object.
```

a varibale can be restericted to never have ownership or always have ownership
of an object

```typescript
var foo : object owning = new object();
var bar : object renting = foo; 
bar = own foo; //error bar cannot own an object
```

before you assign an object to an variable you need to assure that this variable
does not already own a differetn object

```typescript
var foo = new object();
foo = new object(); // error foo does already owns an object that first needs to be deleted
```
```typescript
var foo = new object();
delete foo;
foo = new object(); // ok
```

If you know that a condition can't be false, like an object is never deleted at
that point, but the compiler can't know that, you can use `!` to tell it you
know what you do.

```typescript
var foo = // from somewhere we do not know if it is already deleted
foo!.something()
```
This will assume that delete will work and will not enforce you to handle a case
where foo is already deleted. If your wrong this will raise an error and
propably crach your Program.


# Async

No Method call should block. Operations that will run for multiple frames should
return a Task or Task<T>.

# Threading

While multithreading is supported, the main focus is on non multi thread
interaction.

Threads are better described as event queues. One Thread can "inject" code on  
another thread by appending tasks to the event queue.

Every Object is asigned a thread. Only that thread can access the object. Every
object that is passed in as a parameter to a method must be assigned to the
thread that performs the call. The instance the method is called on (if not
static) also needs to be assigned to the current thread otherwise the call would
be iligal.

Since the above constraints every instance referenced by a (non static) filed
the object owns is alsow assigned to the current thread.

If an static field is accessed it is not gurantied that it is assigned to the
current thread, in that case before the object can be used this need to be
checked.

## named Threads

A named thread is a Thread defined at compiletime. An Object, Method, Field,
etc... can be marked to be only accessible from the named thread (e.g. UI). An
Method marked for an named thread does not need to perform checks to use other
methods/fields that are marked with the same named thread.

## shared objects

In order to comunicate between different threads, you can created shared objects
`new shared object()`. The complete Api surface is implicitly async, every call
to a Method or Field needs to be awaited.

All fields are transparently behind an async read/write-lock.

> Can an shared object have methods without restrictions? Deadlock? 