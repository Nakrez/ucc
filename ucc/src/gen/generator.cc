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

#include <gen/generator.hh>
#include <type/function.hh>

using namespace ucc;
using namespace gen;
using namespace ucmp;
using namespace ir;

Generator::Generator(ucmp::ir::Context& c)
    : gen_(c)
    , c_(c)
    , val_(nullptr)
{
    gen_.init();
}

Generator::~Generator()
{}

void Generator::operator()(const ast::FunctionDecl& ast)
{
    if (ast.compound_get())
    {
        const type::Function* ft;
        ucmp::ir::sType ret;

        ft = dynamic_cast<const type::Function*> (ast.built_type_get());
        ret = ft->return_type_get()->to_ir_type(c_);

        gen_.start_function(ast.name_get(), ret);

        BasicBlock* bb = new BasicBlock(c_, gen_.declared_function_get(),
                                        ast.name_get());
        gen_.insert_pt_set(bb);

        gen_.end_function();
    }
}
