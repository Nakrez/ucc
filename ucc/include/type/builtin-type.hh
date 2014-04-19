/*
Copyright (C) 2014 Baptiste Covolato <b.covolato@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef UCC_TYPE_BUILTIN_TYPE_HH
# define UCC_TYPE_BUILTIN_TYPE_HH

# include <type/floating-point.hh>
# include <type/signed-integer.hh>
# include <type/unsigned-integer.hh>

namespace ucc
{
    namespace type
    {
        class Float : public FloatingPoint
        {
            Float(const Float&) = delete;
            Float& operator=(const Float&) = delete;

            public:
                virtual ~Float() = default;

                static Float& instance_get()
                {
                    static Float f;

                    return f;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "float";
                }

            private:
                Float() = default;
        };

        class Double : public FloatingPoint
        {
            Double(const Double&) = delete;
            Double& operator=(const Double&) = delete;

            public:
                virtual ~Double() = default;

                static Double& instance_get()
                {
                    static Double d;

                    return d;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "double";
                }

            private:
                Double() = default;
        };

        class Char : public SignedInteger
        {
            Char(const Char&) = delete;
            Char& operator=(const Char&) = delete;

            public:
                virtual ~Char() = default;

                static Char& instance_get()
                {
                    static Char c;

                    return c;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "char";
                }

            private:
                Char() = default;
        };

        class UnsignedChar : public UnsignedInteger
        {
            UnsignedChar(const UnsignedChar&) = delete;
            UnsignedChar& operator=(const UnsignedChar&) = delete;

            public:
                virtual ~UnsignedChar();

                static UnsignedChar& instance_get()
                {
                    static UnsignedChar uc;

                    return uc;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "unsigned char";
                }

            private:
                UnsignedChar() = default;
        };

        class Short : public SignedInteger
        {
            Short(const Short&) = delete;
            Short& operator=(const Short&) = delete;

            public:
                virtual ~Short() = default;

                static Short& instance_get()
                {
                    static Short s;

                    return s;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "short";
                }

            private:
                Short() = default;
        };

        class UnsignedShort : public UnsignedInteger
        {
            UnsignedShort(const UnsignedShort&) = delete;
            UnsignedShort& operator=(const UnsignedShort&) = delete;

            public:
                virtual ~UnsignedShort() = default;

                static UnsignedShort& instance_get()
                {
                    static UnsignedShort us;

                    return us;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "unsigned short";
                }

            private:
                UnsignedShort() = default;
        };

        class Int : public SignedInteger
        {
            Int(const Int&) = delete;
            Int& operator=(const Int&) = delete;

            public:
                virtual ~Int() = default;

                static Int& instance_get()
                {
                    static Int i;

                    return i;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "int";
                }

            private:
                Int() = default;
        };

        class UnsignedInt : public UnsignedInteger
        {
            UnsignedInt(const UnsignedInt&) = delete;
            UnsignedInt& operator=(const UnsignedInt&) = delete;

            public:
                virtual ~UnsignedInt() = default;

                static UnsignedInt& instance_get()
                {
                    static UnsignedInt ui;

                    return ui;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "unsigned int";
                }

            private:
                UnsignedInt() = default;
        };

        class Long : public SignedInteger
        {
            Long(const Long&) = delete;
            Long& operator=(const Long&) = delete;

            public:
                virtual ~Long() = default;

                static Long& instance_get()
                {
                    static Long l;

                    return l;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "long";
                }

            private:
                Long() = default;
        };

        class UnsignedLong : public UnsignedInteger
        {
            UnsignedLong(const UnsignedLong&) = delete;
            UnsignedLong& operator=(const UnsignedLong&) = delete;

            public:
                virtual ~UnsignedLong() = default;

                static UnsignedLong& instance_get()
                {
                    static UnsignedLong ul;

                    return ul;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "unsigned long";
                }

            private:
                UnsignedLong() = default;
        };

        class LongLong : public SignedInteger
        {
            LongLong(const LongLong&) = delete;
            LongLong& operator=(const LongLong&) = delete;

            public:
                virtual ~LongLong() = default;

                static LongLong& instance_get()
                {
                    static LongLong ll;

                    return ll;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "long long";
                }

            private:
                LongLong() = default;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_BUILTIN_TYPE_HH */
