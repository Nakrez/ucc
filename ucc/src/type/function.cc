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

#include <type/function.hh>
#include <ucmp/ir/function-type.hh>

using namespace ucc;
using namespace type;

Function::Function(const Type* return_type)
    : return_type_(return_type)
    , args_("")
    , has_elipsis_(false)
{}

Function::~Function()
{}

bool Function::operator==(const Type& t) const
{
    const Function* f = dynamic_cast<const Function*> (&t.actual_type());

    if (!f)
        return false;

    if (size_get() == 0)
        return true;

    if (f->size_get() == 0)
        return true;

    if (no_param() != f->no_param())
        return false;

    if (has_elipsis_ != f->has_elipsis())
        return false;

    if (size_get() != f->size_get())
        return false;

    auto it = f->cbegin();
    auto tit = cbegin();
    auto tend = cend();

    for (; tit != tend; ++tit, ++it)
    {
        if (*tit->type_get() != *it->type_get())
            return false;
    }

    return true;
}

std::string Function::to_str() const
{
    std::string args = return_type_->to_str() + "(";
    auto begin = args_.cbegin();
    auto it = args_.cbegin();
    auto end = args_.cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            args += ", ";

        args += (*it).type_get()->to_str();
    }

    if (has_elipsis())
    {
        if (args_.size_get() > 0)
            args += ", ";
        args += "...";
    }
    return args + ")";
}

ucmp::ir::sType Function::to_ir_type(ucmp::ir::Context& c) const
{
    ucmp::ir::FunctionType *t;

    t = new ucmp::ir::FunctionType(return_type_->to_ir_type(c));

    for (auto f : args_)
        t->arg_add(f.type_get()->to_ir_type(c));

    return ucmp::ir::sType(t);
}
