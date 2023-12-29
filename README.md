# Aleksandra
A custom programming language with built for speed and simplicity.

## Usage
```shell
$ ./Aleksandra myProgram.dra
```

## Pipeline
This section describes the inner workings of the compiler providing detailed breakdowns of each stage.
### Source Code
```swift
// Example *.dra code
Import StandardIO;

Function main() -> Integer 
{
    std::print("Hello, World!");

    Return 0;
}
```

### Lexer 
Responsible for breaking the preprocessed source code down into a list of tokens, each `Token` having a `type` and a `text` associated with them, before sending the list to the AST. An example has been provided to show what the potential output of the [Source Code](#source-code).

```shell
Token[0]:
        Type: Keyword
        Text: "Import"
Token[1]:
        Type: Identifier
        Text: "StandardIO"
Token[2]:
        Type: Punctuation
        Text: ";"
Token[3]:
        Type: Keyword
        Text: "Function"
Token[4]:
        Type: Identifier
        Text: "main"
Token[5]:
        Type: Punctuation
        Text: "("
Token[6]:
        Type: Punctuation
        Text: ")"
Token[7]:
        Type: Operator
        Text: "->"
Token[8]:
        Type: Keyword
        Text: "Integer"
Token[9]:
        Type: Punctuation
        Text: "{"
Token[10]:
        Type: Identifier
        Text: "std"
Token[11]:
        Type: Operator
        Text: "::"
Token[12]:
        Type: Identifier
        Text: "print"
Token[13]:
        Type: Punctuation
        Text: "("
Token[14]:
        Type: Literal
        Text: "Hello, World!"
Token[15]:
        Type: Punctuation
        Text: ")"
Token[16]:
        Type: Punctuation
        Text: ";"
Token[17]:
        Type: Keyword
        Text: "Return"
Token[18]:
        Type: Number
        Text: "0"
Token[19]:
        Type: Punctuation
        Text: ";"
Token[20]:
        Type: Punctuation
        Text: "}"
```

### Building