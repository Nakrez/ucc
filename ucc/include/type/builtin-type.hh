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
                /// Destructor
                virtual ~Float() = default;

                /// Return the Float singleton instance
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
                /// Constructor
                Float() = default;
        };

        class Double : public FloatingPoint
        {
            Double(const Double&) = delete;
            Double& operator=(const Double&) = delete;

            public:
                /// Destructor
                virtual ~Double() = default;

                /// Return the Double singleton instance
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
                /// Constructor
                Double() = default;
        };

        class Char : public SignedInteger
        {
            Char(const Char&) = delete;
            Char& operator=(const Char&) = delete;

            public:
                /// Destructor
                virtual ~Char() = default;

                /// Return the Char singleton instance
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
                /// Constructor
                Char() = default;
        };

        class UnsignedChar : public UnsignedInteger
        {
            UnsignedChar(const UnsignedChar&) = delete;
            UnsignedChar& operator=(const UnsignedChar&) = delete;

            public:
                /// Destructor
                virtual ~UnsignedChar() = default;

                /// Return the UnsignedChar singleton instance
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
                /// Constructor
                UnsignedChar() = default;
        };

        class Short : public SignedInteger
        {
            Short(const Short&) = delete;
            Short& operator=(const Short&) = delete;

            public:
                /// Destructor
                virtual ~Short() = default;

                /// Return the Short singleton instance
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
                /// Constructor
                Short() = default;
        };

        class UnsignedShort : public UnsignedInteger
        {
            UnsignedShort(const UnsignedShort&) = delete;
            UnsignedShort& operator=(const UnsignedShort&) = delete;

            public:
                /// Destructor
                virtual ~UnsignedShort() = default;

                /// Return the UnsignedShort singleton instance
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
                /// Constructor
                UnsignedShort() = default;
        };

        class Int : public SignedInteger
        {
            Int(const Int&) = delete;
            Int& operator=(const Int&) = delete;

            public:
                /// Destructor
                virtual ~Int() = default;

                /// Return the Int singleton instance
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
                /// Constructor
                Int() = default;
        };

        class UnsignedInt : public UnsignedInteger
        {
            UnsignedInt(const UnsignedInt&) = delete;
            UnsignedInt& operator=(const UnsignedInt&) = delete;

            public:
                /// Destructor
                virtual ~UnsignedInt() = default;

                /// Return the UnsignedInt singleton instance
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
                /// Constructor
                UnsignedInt() = default;
        };

        class Long : public SignedInteger
        {
            Long(const Long&) = delete;
            Long& operator=(const Long&) = delete;

            public:
                /// Destructor
                virtual ~Long() = default;

                /// Return the Long singleton instance
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
                /// Constructor
                Long() = default;
        };

        class UnsignedLong : public UnsignedInteger
        {
            UnsignedLong(const UnsignedLong&) = delete;
            UnsignedLong& operator=(const UnsignedLong&) = delete;

            public:
                /// Destructor
                virtual ~UnsignedLong() = default;

                /// Return the UnsignedLong singleton instance
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
                /// Constructor
                UnsignedLong() = default;
        };

        class LongLong : public SignedInteger
        {
            LongLong(const LongLong&) = delete;
            LongLong& operator=(const LongLong&) = delete;

            public:
                /// Destructor
                virtual ~LongLong() = default;

                /// Return the LongLong singleton instance
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
                /// Constructor
                LongLong() = default;
        };

        class UnsignedLongLong : public UnsignedInteger
        {
            UnsignedLongLong(const UnsignedLongLong&) = delete;
            UnsignedLongLong& operator=(const UnsignedLongLong&) = delete;

            public:
                /// Destructor
                virtual ~UnsignedLongLong() = default;

                /// Return the UnsignedLongLong singleton instance
                static UnsignedLongLong& instance_get()
                {
                    static UnsignedLongLong ull;

                    return ull;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "unsigned long long";
                }

            private:
                /// Constructor
                UnsignedLongLong() = default;
        };


        class Void : public Type
        {
            Void(const Void&) = delete;
            Void& operator=(const Void&) = delete;

            public:
                /// Destructor
                virtual ~Void() = default;

                /// Return the Void singleton instance
                static Void& instance_get()
                {
                    static Void v;

                    return v;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type& t) const override
                {
                    if (&t == this)
                        return Type::TypeCompatibility::full;

                    return Type::TypeCompatibility::error;
                }

                virtual TypeCompatibility
                compatible_on_op(const Type&, ast::OpExpr::Op) const override
                {
                    return Type::TypeCompatibility::error;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    return "void";
                }

            private:
                /// Constructor
                Void() = default;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_BUILTIN_TYPE_HH */
