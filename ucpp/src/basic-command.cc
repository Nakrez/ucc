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

#include <basic-command.hh>
#include <command.hh>

BasicCommand::BasicCommand(const std::string& opt,
                           const std::string& description,
                           const std::string& dependancies)
    : desc_(description)
    , dep_(dependancies)
{
    if (opt.size() > 2)
    {
        if (opt.at(1) == '|')
        {
            short_opt_ = opt.at(0);
            long_opt_ = opt.substr(2, opt.size() - 2);
        }
        else
            long_opt_ = opt;
    }
    else if (opt.size() == 1)
        short_opt_ = opt.at(0);

    Command::instance().register_command(this);
}

BasicCommand::~BasicCommand()
{}

const std::string& BasicCommand::long_opt_get() const
{
    return long_opt_;
}

int BasicCommand::short_opt_get() const
{
    return short_opt_;
}

const std::string& BasicCommand::desc_get() const
{
    return desc_;
}

const std::string& BasicCommand::dep_get() const
{
    return dep_;
}
