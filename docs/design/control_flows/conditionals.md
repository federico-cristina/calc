# Conditional Control Flows

<!--
Copyright (c) 2024 Federico Cristina

This file is part of the calc scripting language project,
under the Apache License v2.0. See LICENSE for license
informations.
-->

In **calc** there are two major kinds of conditionals: simple selections, and multiple
selections and both them groups one, or more, lexical constructs.

## Simple Selections

Simple selections, or simple conditionals, evaluates a simple boolean (or not if auto
cast is avaible) conditional expression and, depending on the result, a statement can
be skipped or executed.

To provide simple selection, there are `if` and `else` keywords, with the following
syntax:

> `if` `(`*condition<sub>0</sub>*`)` \
>     *statememt<sub>0</sub>* \
> `else if` `(`*condition<sub>1</sub>*`)` \
>     *statememt<sub>1</sub>* \
> ... \
> `else if` `(`*condition<sub>n</sub>*`)` \
>     *statememt<sub>n</sub>* \
> `else` \
>     *statememt<sub>n + 1</sub>*

or, simplier:

> `if` `(`*condition*`)` \
>     *statememt<sub>0</sub>* \
> `else` \
>     *statememt<sub>1</sub>*

where, in both cases, `else` and `else if` branches are optional.

Only one *statement* will be executed, and only the strictly necessary amouny of *condition*s
will be evaluated. For example, in code:

```c

if (fruit.IsYellow())
    println("Banana!");
else if (fruit.IsOrange())
    println("Orange!");
else if (fruit.IsGreen())
    println("Apple!");
else
    println("Vegetable!");

```

the first *condition* `fruit.IsYellow()` will be evaluated surely, but others will be evaluated
if and only if that *condition* results `false`, and will be executed only the *statement* under
the right *condition*, or the one under `else` keyword.

### Simple Selection As Expression

In **calc** there is also an expression form for the simple selection contruction, the conditional
ternary expression common in C-family languages:

> *condition* `?` *expression<sub>0</sub>* `:` *expression<sub>1</sub>*

For example, the code:

```c

fruitColor = fruit.HasColor() ? fruit.GetColor() : "None";

```

is the expressive form of the equivalent `if`-`else` construction:

```c

if (fruit.HasColor())
    fruitColor = fruit.GetColor();
else
    fruitColor = "None";

```

notice that expressive form of simple selection construction cannot elide the `else` clause and
it must always return a value, so with this construction are commonly used a nullable type and the
`null` value:

```c#

fruitColor = fruit.HasColor() ? fruit.GetColor() : null;

```

<!-- TODO:

## Multiple Selections

Multiple selections, as their name says, are selection operations performed on more than one
value at time. This means that on several related conditions could be better to use a multiple
selection construction, that is optimized to do so.

### Switch Construction

The most common construction to perform multiple selections related to each other, with a single
value on which switch. Switch construction follow the following syntax:

> `switch` `(`*expression*`)`

--!>
