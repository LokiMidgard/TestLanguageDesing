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
                
            This is a problem for the parser, rethink :(
				    vvvvv
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
-|-
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


## Members

Members can be put on types or (namespaces ?? somthing like global methods and propertys...).
### Fields
Internal data that stores the state of a type.

```typescript
type Person {
	name:string
	age:int
} 
```
Fields can only be accessed from methods inside this object, or child objects (see below)
If you need the data to be accessable from the outside, use Properties.

### Propertys

Data that can be accesed from extern.

```typescript
type Person{
	Age:int { get;set; }
	Name: string{
		name:string
		get{
			return name;
		}
		set {
			name = value
		}
	}
}
```

You can define Propertys with an automatic implemented get and set or explecitly
implement it. If you explicitly implement a get and set you can declare the
field where the value gets stored inside the property so it can't be changed
without the use of the set. The setter has implicite a variable `value` that
holds the assignement.

You can also add parameters to a property
```typescript
type PersonRegister{
	age[name:'Paul'| 'Max']:int {
		get{
			if(name == 'Pault')	{
				return 20;
			}
			else {
				return 22;
			}
		}
	}
}
```
You can use ahe default implementaiton with parameters, in that case the
retunrtype must include undefined. 

```typescript
type PersonRegister{
	age[name:string]:int|undefined { get; set; }
}
```

It will store its values in an Hashmap. And returns undefined if the key is not
present. Setting the value undefined will remove the element from the Hashmap.

### Indexer



You can add an indexer to a type which looks simular to the parameter of an
property. and works the same.

```
type MyList{
	this[index:int]: string|undefined{
		get;
		set;
	}
}
```

### Method

A Method executes some code or calculates something.

```typescript
 Add(a:int,b:int) {
	return a + b;
}
```

A method on a type must either be  `pure` or `changing`.

```typescript

type Person {
	lastname:string;
	surname:string;
	middlename:string|undefined;

	changing marry(newName:string){
		lastname = newName;
	}

	pure hasMiddlename():boolean{
		return middlename is not undefined;
	}
}

```

It is an error to change the state of an Object in an pure method. No changing
method may be called inside it.

You can also specify which fields get changed explicitly.

```typescript

type Person {
	lastname:string;
	surname:string;
	middlename:string|undefined;

	changing(lastname) marry(newName:string){
		lastname = newName;
	}

	pure hasMiddlename():boolean{
		return middlename is not undefined;
	}
}

```

> Can this be inferred? Only explicitly set for public methods...  
> This should also be used on parameters. Does the method change values on
> objects passed in
>
> Is recursion then a problem? - No I don't think so, since it doesn't
> matter what value is changed for a specific input, but if there is any
> call that would change somthing. Defining pure for diferent inputs would 
> be problematic for the public surface if it needs to get defined.


>  This could be a little bit complicated. But it is probably only nessasery of
>  library's, and there maybe only for the standard library. And not using this
>  advanced feature will not make the code not functioning
>  
>  changing can define how values can change after the call. In the example below
>  calling add will increas this.Length by one, while remove will decrease it or
>  leave it as is.
>  
>  Without the assignment the value might change, with the assignment we know how.
>  
>  ```typescript
>  type List{
>  	this[index:int >= 0 < this.Length ] {
>  		get {
>  			//get value
>  		}
>  	}
>  
>  	Length:int >0= {
>  		get{
>  			// length
>  		}
>  	}
>  
>  	changing(this.Length = this.Length + 1,this[int] ) add(data:object){
>  		//add
>  	}
>  
>  	changing(this.Length = this.Length - 1| this.Length,this[int]  ) remove(data:object){
>  		//removes if present
>  	}
>  
>  
>  }
>  ```

### Event
An event is an list of functions that can be invoked like a function, and
normaly filed from extern


```typescript

type Person {
	Name:string{
		name:string
		get{
  			return name;
		}
		set{
			name = value;
			NameChanged(name);
		}
	}
	event  NameChanged : (newName:string)=>void;
}

const p = new Person();
p.NameChanged += (theNewName)=> Debug.Write(theNewName);

p.Name = 'Max' // will raise the event which invokes the method above to write to the console.

```

There are two types of events `serial` and `chained`. The default event is a
`serial event`. If the callback has a return type the call invocation of the event
will return an Array with the results.

```typescript
serial event Foo: (bar:int)=>int;
Foo += bar => bar +1;
Foo += bar => bar -1;
const result = Foo(3); 
// result is [4,2]
```

A `chained event` will invoke one function after the other providing the result
of the previous to the next. A Function for a `chained event` must its return
type as its last parameter.

```typescript
chained event Foo: (bar:string)=>string;
Foo += bar => bar + 'foo';
Foo += bar => bar + 'bar';
const result = Foo('empty'); 
// result is "emptyfoobar"
```

You can explicitly implement events like you can explicitly controle what an
property does. You must define the return type for invoke.

```typescript
event Foo:(bar:string)=>string{
	const list = List<(bar:string)=>string>();
	add{
		list.add(value);
	}
	remove{
		list.remove(value);
	}
	invoke : string{
		// whatever invocation does...
	}
}
```


### constructor
Todo....

# Async

No Method call should block. Operations that will run for multiple frames should
return a Task or Task\<T\>.

You can use the `await` keyword in front of a Task or Task\<T\> to pause the
execution until the result is present. The Thread will do other work on the
same thread, if available. In order to use `await`, the current scope must be async.
E.g. The method or property must be marked with async

You can make Propertys `async`, in that case the set method returns a `Task` and
the get a `Task<T>` where `T` is the Property type.

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

Every Thread has an special Type that allows managing it
```typescript
type Thread{
	static current:Thread { get;}
	IsRunning: bool { get;}
	Run<...TArgs:Type is shared,TResult>(...args:TArgs, work: (...TArgs)=>TResult):Task<TResult>
	HasAccess:bool {get;}
}
```

## named Threads

A named thread is a Thread defined at compiletime. An Object, Method, Field,
etc... can be marked to be only accessible from the named thread (e.g. UI). An
Method marked for an named thread does not need to perform checks to use other
methods/fields that are marked with the same named thread.

```
thread Ui;
```

To set the thread explicitly for a method, type, etc... use `on`

```typescript
Draw() on Ui:string{
	// do something
}
```
This method can only be called from the Ui Thread.
You either need already now your on the Ui thread,

```typescript
// we are on the Ui Thread
Draw();
```

Check if we are on the Ui Thread

```typescript
// we are on the Ui Thread
if(Ui.HasAccess){
Draw();
}
```

Or post whatever we want to do on the UI thread
```typescript
Ui.Run(()=>Draw());
```



## shared objects

In order to comunicate between different threads, you can created shared objects
`new shared object()`. The complete Api surface is implicitly async, every call
to a Method or Field needs to be awaited.

All fields are transparently behind an async read/write-lock.

> Can an shared object have methods without restrictions? Deadlock? 


## Visibility

There are following visibilitys

- **private**  
  Only accecable by the owning scope and every member on the same scope.
- **parent**  
  Same as private but one scope higher also can access the member.
- **internal**  
  Everyone in the assembly can access the type.
- **public**  
  Everyone can access the member.
- **protected**  
  Only valid for member in Types, all inheriting internal types can access the
  member. Use public in addition so all inheriting types can access the member.

The default visibility is private.


## Exceptions

> No exceptions?  
> Checked Exception?
>
> ----------------
> 
> Using no exceptions instead the return type will has an Error Object intersected
> with the result.
> 
> Before you use the result you need to check if there was an error.
> 
> Drawback if you perform multiple file operations you need to handle every seperate.
> With exceptions you could catch the exception around the complete block.
> 
> -----------------
> Using exceptions you need to know which exceptions can get thrown by which method.
> 
> In languages like c# that is not always good documented, so you either just catch `Exception`
> everywhere or get surprised by an exception that was not documented in production.
> 
> Java on the other side uses checked exceptions, you need to declare in the
> signiture which exceptions get thrown. This has the drawback, that you often
> need to add a throws declaration to multiple methods that call each other until
> you reach the point where you want to handle it. 
> 
> --------

Possible solution checked exceptions light. Only public available methods need
to declare a `throws` declaration. So the public surface of your code will
define what Exceptions can be thrown. But your internal code does not need that.
Instead it can be staticky interfered. A future editor can show what methods
will throw what exception without the user defining them.

A method can be marked with `throws none` so an error is emitted when the method
could throw an Exception even when it is not public.

> Will this work for internal events? - I think...

This means adding an Exception to an public method is a breaking change. If a
library provides event's the functions registerd may not throw unless explicitly
defined.

An alternative could be that events always throw `Exception` unless opted out. That way
the author of the event can't (or at least not so easy) forget to think about it.

Besides Exceptions there would be Errors. Those are extrem failures like
OutOfMemory, or NullReference exception that show a serve problem in the code.
They should generaly not be catched and crash the program.

Can errors that often happen staticly checked and prevented.

|error|can be prevented|
|-|-|
|Nullreference|Should be handeled by static type checking, a variable can only be null if declared that way. And as long it is not a shared object and no await was between a check we now it will not be changed. An Error here that will crash the program is Ok.
|IndexOutOfBounds| A solution could be instead of throwing returning `undefined`. You would still need to check for undefiend after every access :(. A Better way could be to add a constraint to the size of the array/list/etc. `int:>=0 <this.Length`. The pure property of methods would make it managable. however calling add or remove on a list would still make it nessesarry to check the range again before using the index.  |