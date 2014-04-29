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

#ifndef UCC_MISC_DIAGNOSTIC_REPORTER_HH
# define UCC_MISC_DIAGNOSTIC_REPORTER_HH

# include <ostream>
# include <list>

# include <misc/diagnostic.hh>

namespace ucc
{
    namespace misc
    {
        class DiagnosticReporter
        {
            DiagnosticReporter(const DiagnosticReporter&) = delete;
            DiagnosticReporter& operator=(const DiagnosticReporter&) = delete;

            public:
                class Error
                {
                    public:
                        Error() = default;
                        ~Error() = default;
                };

            public:
                static DiagnosticReporter& instance_get()
                {
                    static DiagnosticReporter reporter;

                    return reporter;
                }

                void set_warning_as_error()
                {
                    warning_as_error_ = true;
                }

                void disable_warning()
                {
                    disable_warning_ = true;
                }

                Diagnostic::Type error_type_get() const
                {
                    return error_;
                }

                void throw_on_error();
                void add(Diagnostic& d);
                void flush(std::ostream& o);

            private:
                DiagnosticReporter()
                    : warning_as_error_(false)
                    , disable_warning_(false)
                    , error_(Diagnostic::Type::none)
                    , diags_()
                {}

            private:
                bool warning_as_error_;
                bool disable_warning_;

                Diagnostic::Type error_;
                std::list<Diagnostic> diags_;
        };
    } // namespace misc
} // namespace ucc

#endif /* !UCC_MISC_DIAGNOSTIC_REPORTER_HH */
