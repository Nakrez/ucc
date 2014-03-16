#ifndef UCC_MISC_ERROR_HH
# define UCC_MISC_ERROR_HH

# include <string>
# include <sstream>
# include <iostream>

namespace ucc
{
    namespace misc
    {
        class Error
        {
            public:
                enum Type
                {
                    none = 0,
                    compiler = 1,
                    lex = 2,
                    parse = 3,
                };

            public:
                Error();
                Error(const Error& err);
                ~Error();

                Error& operator=(const Error& err);

                Error& operator<<(Type type);
                Error& operator<<(const std::string& msg);
                Error& operator<<(std::ostream& (*msg) (std::ostream&));

                template <class T>
                Error& operator<<(const T& t);

                void throw_on_error() const;

                std::string msg_get() const;
                Type error_code_get() const;

            private:
                Type err_code_;
                std::stringstream msg_;
        };
    } // namespace misc
} // namespace ucc

# include <misc/error.hxx>

#endif /* !UCC_MISC_ERROR_HH */
