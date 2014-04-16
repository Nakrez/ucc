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

#include <misc/diagnostic-reporter.hh>

using namespace ucc;
using namespace misc;

void DiagnosticReporter::throw_on_error()
{
    if (error_ != Diagnostic::Type::none)
        throw DiagnosticReporter::Error();
}

void DiagnosticReporter::add(Diagnostic& d)
{
    if (disable_warning_ && d.severity_get() == Diagnostic::Severity::warn)
        return;

    if (warning_as_error_ && d.severity_get() == Diagnostic::Severity::warn)
        d.severity_set(Diagnostic::Severity::err);

    diags_.push_back(d);

    if (warning_as_error_ || d.severity_get() != Diagnostic::Severity::warn)
    {
        if (error_ == Diagnostic::Type::none || error_ > d.type_get())
            error_ = d.type_get();
    }

    if (d.severity_get() == Diagnostic::Severity::critical)
        throw DiagnosticReporter::Error();
}

void DiagnosticReporter::flush(std::ostream& o)
{
    for (auto d : diags_)
    {
        o << d.location_get() << ": ";

        if (d.type_get() == Diagnostic::Type::internal)
            o << "internal ucc error: ";
        else
        {
            switch (d.severity_get())
            {
                case Diagnostic::Severity::warn:
                    o << "warning: ";
                    break;
                case Diagnostic::Severity::err:
                    o << "error: ";
                    break;
                case Diagnostic::Severity::critical:
                    o << "critical error: ";
                    break;
            }
        }

        o << d.msg_get() << std::endl;
    }

    diags_.clear();
}
