#ifndef UCC_MISC_ERROR_HXX
# define UCC_MISC_ERROR_HXX

# include <misc/error.hh>

namespace ucc
{
    namespace misc
    {
        inline Error::Error()
            : err_code_(Type::none)
            , msg_()
        {}

        inline Error::Error(const Error& err)
            : err_code_(err.error_code_get())
            , msg_(err.msg_get())
        {}

        inline Error::~Error()
        {}

        inline Error& Error::operator=(const Error& err)
        {
            err_code_ = err.err_code_;
            msg_ << err.msg_;

            return *this;
        }

        inline Error& Error::operator<<(Type type)
        {
            if (err_code_ == Type::none || err_code_ > type)
                err_code_ = type;

            return *this;
        }

        inline Error& Error::operator<<(const std::string& msg)
        {
            msg_ << msg;

            return *this;
        }

        inline Error& Error::operator<<(std::ostream& (*msg) (std::ostream&))
        {
            msg_ << msg;

            return *this;
        }

        template <class T>
        Error& Error::operator<<(const T& t)
        {
            msg_ << t;

            return *this;
        }

        inline void Error::throw_on_error() const
        {
            if (err_code_ > Type::none)
                throw *this;
        }

        inline std::string Error::msg_get() const
        {
            return msg_.str();
        }

        inline Error::Type Error::error_code_get() const
        {
            return err_code_;
        }
    } // namespace misc
} // namespace ucc

#endif /* !UCC_MISC_ERROR_HXX */
