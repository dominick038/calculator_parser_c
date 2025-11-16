# Calculator Parser → Language Development Roadmap

A structured learning path from calculator parser to full programming language implementation.

---

## Phase 1: Fix Bugs
**Goal:** Make the calculator robust with proper error handling
**Learning Focus:** Defensive programming, input validation, error handling patterns
**Estimated Time:** 1-2 hours

### Tasks:
- [ ] Add stack bounds checking in `parser.c`
  - [ ] Check `stack_top >= 1` before popping operands (lines 59-62)
  - [ ] Validate exactly one value remains after evaluation (line 83)
  - [ ] Return proper error instead of crashing
- [ ] Handle malformed expressions
  - [ ] Detect trailing operators (e.g., "5/", "1+1++")
  - [ ] Detect leading operators (e.g., "++1")
  - [ ] Detect missing operators (e.g., "10 10")
  - [ ] Handle empty input gracefully
- [ ] Add error message reporting
  - [ ] Print helpful error messages to stderr
  - [ ] Consider adding error position/context
- [ ] Test edge cases
  - [ ] Division by zero handling (currently returns "inf")
  - [ ] Very large numbers (buffer overflow in `extract_digit`)
  - [ ] Maximum expression complexity
- [ ] Update `main.c` to handle errors properly
  - [ ] Check for NULL/error returns from `parser_evaluate`
  - [ ] Exit with non-zero code on errors
  - [ ] Add usage message when no args provided

**Success Criteria:** All invalid inputs produce helpful errors instead of crashes

---

## Phase 2: Make More Extensible
**Goal:** Refactor architecture to make adding features easy
**Learning Focus:** Code architecture, separation of concerns, abstraction patterns
**Estimated Time:** 2-4 hours

### Tasks:
- [ ] Create operator abstraction system
  - [ ] Define `Operator` struct with precedence and evaluation function
  - [ ] Build operator registry/table
  - [ ] Replace hardcoded switch statements with table lookups
  - [ ] Refactor precedence array to be part of operator definitions
- [ ] Improve error handling architecture
  - [ ] Define `EvalResult` or similar result type
  - [ ] Replace `const char*` returns with proper result types
  - [ ] Implement error propagation through call stack
  - [ ] Remove static buffer in `parser_evaluate` (not thread-safe)
- [ ] Separate parsing from evaluation
  - [ ] Split `parser_evaluate` into two functions:
    - `parse_to_rpn()` - converts infix to RPN queue
    - `evaluate_rpn()` - evaluates RPN queue to result
  - [ ] Makes testing and debugging easier
- [ ] Improve tokenizer robustness
  - [ ] Add proper buffer overflow protection in `extract_digit`
  - [ ] Consider supporting floating point literals
  - [ ] Better error reporting (include position in input)
- [ ] Fix memory management issues
  - [ ] Ensure `tokenizer_free` cleans up current token if needed
  - [ ] Audit all malloc calls for null checks
  - [ ] Add memory leak tests with valgrind/asan

**Success Criteria:** Adding a new operator should be ~5 lines of code, not modifying multiple files

---

## Phase 3: Add More Mathematical Operators
**Goal:** Extend calculator capabilities, validate extensibility work
**Learning Focus:** How well Phase 2 worked, operator precedence, associativity
**Estimated Time:** 1-2 hours (if Phase 2 done well)

### Tasks:
- [ ] Add modulo operator (`%`)
  - [ ] Add `TOKEN_MOD` to TokenType enum
  - [ ] Add tokenizer pattern for `%`
  - [ ] Define operator precedence (same as multiply/divide)
  - [ ] Add evaluation function
  - [ ] Handle modulo by zero
- [ ] Add exponentiation operator (`^` or `**`)
  - [ ] Add `TOKEN_POWER` to TokenType enum
  - [ ] Decide on symbol: `^` or `**`
  - [ ] Define precedence (higher than multiply)
  - [ ] **Important:** Right-associative (2^3^2 = 2^9, not 8^2)
  - [ ] Use `pow()` from math.h
- [ ] Add unary minus support (optional, tricky)
  - [ ] Distinguish `-5` from `5-3`
  - [ ] May require parser lookahead
  - [ ] Consider unary plus as well
- [ ] Add bitwise operators (optional)
  - [ ] `&` (AND), `|` (OR), `^` (XOR)
  - [ ] `<<` (left shift), `>>` (right shift)
  - [ ] `~` (NOT, unary)
  - [ ] Requires casting to int for operations
- [ ] Add comparison operators (optional)
  - [ ] `==`, `!=`, `<`, `>`, `<=`, `>=`
  - [ ] Returns 1.0 (true) or 0.0 (false)
- [ ] Update tests for all new operators
  - [ ] Write test cases covering precedence
  - [ ] Test associativity (especially for power)
  - [ ] Test edge cases

**Success Criteria:** Adding each new operator takes < 30 minutes

---

## Phase 4: Add Variables
**Goal:** Implement variable assignment and lookup
**Learning Focus:** Symbol tables, environments, scoping, parse vs eval phases
**Estimated Time:** 3-6 hours

### Tasks:
- [ ] Design and implement Environment/Symbol Table
  - [ ] Create `Environment` struct to store variables
  - [ ] Implement variable storage (hash map or dynamic array)
  - [ ] Implement `env_set(name, value)` for assignment
  - [ ] Implement `env_get(name)` for lookup
  - [ ] Handle undefined variable errors
- [ ] Extend tokenizer for identifiers
  - [ ] Add `TOKEN_IDENTIFIER` type
  - [ ] Tokenize variable names (e.g., `[a-zA-Z_][a-zA-Z0-9_]*`)
  - [ ] Store identifier string in token
- [ ] Add assignment operator
  - [ ] Add `TOKEN_ASSIGN` for `=`
  - [ ] Distinguish assignment from equality (if adding `==`)
  - [ ] Parse assignment statements (e.g., `x = 5`)
  - [ ] Assignment should return the assigned value
- [ ] Modify parser to handle variables
  - [ ] Treat identifiers as values during parsing
  - [ ] Variable lookup happens during evaluation, not parsing
  - [ ] Store identifier tokens in RPN queue
- [ ] Modify evaluator to support variables
  - [ ] During RPN evaluation, look up variable values
  - [ ] Handle undefined variable errors
  - [ ] Handle assignment during evaluation
- [ ] Update main to support multiple expressions
  - [ ] REPL mode: read-eval-print loop
  - [ ] Allow multiple lines of input
  - [ ] Variables persist across expressions
  - [ ] Example:
    ```
    > x = 5
    5
    > y = 3
    3
    > x + y * 2
    11
    ```
- [ ] Consider scoping (optional for now)
  - [ ] Global scope only for now
  - [ ] Block scoping can wait for Phase 5

**Success Criteria:** Can assign variables and use them in expressions with persistence

---

## Phase 5: Build Your Own Programming Language
**Goal:** Design and implement a full programming language from scratch
**Learning Focus:** Language design, AST, advanced parsing, type systems, control flow
**Estimated Time:** Weeks to months (ongoing project)

### Preparation:
- [ ] Read "Crafting Interpreters" by Bob Nystrom
  - [ ] Part I: Tree-Walk Interpreter (Lox language)
  - [ ] Part II: Bytecode Virtual Machine (optional)
- [ ] Or read "Writing An Interpreter In Go" by Thorsten Ball
- [ ] Study other language implementations (Python, Lua, etc.)
- [ ] Decide on language paradigm:
  - [ ] Imperative, functional, object-oriented, or multi-paradigm?
  - [ ] Static or dynamic typing?
  - [ ] Compiled or interpreted?

### Language Design Phase:
- [ ] Define language goals and philosophy
  - [ ] What problem does your language solve?
  - [ ] Who is the target audience?
  - [ ] What makes it unique/interesting?
- [ ] Design syntax
  - [ ] Keywords and operators
  - [ ] Statement vs expression semantics
  - [ ] Block structure (braces, indentation, keywords?)
- [ ] Design type system (if applicable)
  - [ ] Primitive types
  - [ ] Composite types (arrays, structs, etc.)
  - [ ] Type inference vs explicit typing
- [ ] Write example programs in your language
  - [ ] Helps validate design decisions
  - [ ] Identifies missing features

### Core Implementation Tasks:
- [ ] **Lexer/Tokenizer**
  - [ ] Build on calculator tokenizer experience
  - [ ] Support keywords, multi-char operators, string literals
  - [ ] Line/column tracking for error messages
- [ ] **Parser → AST**
  - [ ] Move beyond RPN to Abstract Syntax Tree
  - [ ] Learn recursive descent parsing or Pratt parsing
  - [ ] Parse expressions, statements, declarations
  - [ ] Handle operator precedence properly
- [ ] **Semantic Analysis**
  - [ ] Type checking (if statically typed)
  - [ ] Variable resolution
  - [ ] Scope analysis
- [ ] **Evaluator/Interpreter or Compiler**
  - [ ] Tree-walk interpreter (easiest start)
  - [ ] Or bytecode VM (more complex, more efficient)
  - [ ] Or native compilation (most complex)
- [ ] **Core Language Features**
  - [ ] Variables and assignment (done in Phase 4)
  - [ ] Functions (definition and calls)
  - [ ] Control flow (if, while, for)
  - [ ] Data structures (arrays, objects/structs)
  - [ ] Standard library basics (print, I/O, math)
- [ ] **Advanced Features** (optional)
  - [ ] Closures and first-class functions
  - [ ] Garbage collection
  - [ ] Module system
  - [ ] Generics/templates
  - [ ] Concurrency primitives

### Documentation and Polish:
- [ ] Write comprehensive README
  - [ ] Language overview and philosophy
  - [ ] Installation and usage instructions
  - [ ] Language tutorial with examples
  - [ ] Grammar specification
- [ ] Create example programs
  - [ ] "Hello World"
  - [ ] FizzBuzz
  - [ ] Fibonacci (recursion demo)
  - [ ] Something unique to your language
- [ ] Write tests
  - [ ] Unit tests for lexer, parser, evaluator
  - [ ] Integration tests (full programs)
  - [ ] Test error handling
- [ ] Performance benchmarks (optional)
- [ ] Create project website/docs (optional but impressive)

**Success Criteria:** Can write and execute non-trivial programs in your language

---

## Portfolio Presentation Strategy

### Narrative Arc:
1. **Calculator Parser** (this repo)
   - "Learning project to understand parsing fundamentals"
   - Implements Shunting Yard algorithm
   - Demonstrates C programming and data structure skills
   - Link to language repo with "This was my stepping stone to..."

2. **[Your Language]** (future repo)
   - "Designed and implemented a programming language from scratch"
   - Show progression from calculator
   - Highlight unique features
   - Include example programs
   - Detailed documentation

### README Updates for Calculator:
- [ ] Add section: "Learning Journey"
- [ ] Explain this was practice for building a full language
- [ ] Link to language repo when it exists
- [ ] Show the phases/progression with git tags
- [ ] Keep it polished but brief

### Git Hygiene:
- [ ] Tag each completed phase: `git tag v1.0-bugs-fixed`, etc.
- [ ] Write good commit messages going forward
- [ ] Consider interactive rebase to clean up history (optional)
- [ ] Keep commits atomic and focused

---

## Current Status: Phase 0 (Working Prototype)
✅ Basic calculator works
✅ Shunting Yard algorithm implemented
✅ Stack and Queue data structures
✅ Tokenizer for basic operators
✅ RPN evaluation
⚠️ Crashes on invalid input
⚠️ Limited error handling
⚠️ Not extensible yet

**Next Step:** Begin Phase 1 - Fix Bugs

---

## Notes and Reminders

- Commit after each major task with descriptive messages
- Test thoroughly before moving to next phase
- Don't rush - understanding is more valuable than speed
- Each phase builds on the last - refactoring early pays off later
- Use AddressSanitizer to catch memory bugs: `-fsanitize=address`
- Consider adding a test suite early (Phase 2 or 3)
- Keep this TODO updated as you learn and priorities change

**Remember:** The goal is learning, not perfection. Each phase teaches you something new that prepares you for building a real language.
