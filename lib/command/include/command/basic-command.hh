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

#ifndef BASIC_COMMAND_HH
# define BASIC_COMMAND_HH

# include <string>

namespace command
{
    class Command;

    class BasicCommand
    {
        public:
            BasicCommand(const std::string& opt,
                         const std::string& description,
                         const std::string& dependancies);
            virtual ~BasicCommand();

            virtual void run() = 0;

            const std::string& long_opt_get() const;
            int short_opt_get() const;
            const std::string& desc_get() const;
            const std::string& dep_get() const;

        private:
            std::string long_opt_;
            int short_opt_;
            std::string desc_;
            std::string dep_;
    };
} // namespace command

#endif /* !BASIC_COMMAND_HH */
