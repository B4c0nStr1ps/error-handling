# **error-handling demo project**

The purpose of this demo project is to have a way of handling error like in Rust.
The result.h header contains the implementation of Result<T, E> class. This class uses a std::variant to store a value T or and error E. The values T and E are wrapped using, respectively, Ok<T> and Err<T>. This two wrapper are used to mimic Rust syntax and to handle the T = void case. The cost of the wrapper is one additional move constructor.
If you are interested more in how to handle error in c++ without using exceptions or c-style error codes please watch the talk ["Expect the Expected" by Andrei Alexandrescu](https://www.youtube.com/watch?v=nVzgkepAg5Y) .
For a production ready solution look at the LLVM implementation (Error.h header of LLVMSupport library).
See this lightining talk [Structured Error Handling in LLVM](https://www.youtube.com/watch?v=Wq8fNK98WGw).

### Examples:
Use is_ok or is_err to check if Result is an Ok value or an Error one:

    auto res = divide(8, 4);
    assert(res.is_ok() == true);

    auto res = divide(8, 0);
    assert(res.is_err() == true);

Use unwrap() to get the value. unwrap() will assert if Result is and error.

    auto res = divide(8, 4);
    int value = res.unwrap();

Use unwrap_err() to get the error. unwrap_err() will assert it Result is a value.

    auto res = divide(8, 0);
    std::string error_message = res.unwrap_err();

Pattern matching style syntax:

     auto res = divide(8, 4);
     bs::match_result(res /***PADDING***/,
                      [](const bs::Ok<int>& val) {
                        std::cout << "result = " << val.value << "\n";
                      },
                      [](const bs::Err<std::string>& err) {
                        std::cout << "Division error: " << err.value << "\n";
                      });

See main.cpp for use examples.
