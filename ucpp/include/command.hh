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

#ifndef COMMAND_HH
# define COMMAND_HH

# include <iostream>
# include <list>

# include <basic-command.hh>
# include <callback-command.hh>

# define REGISTER_COMMAND(name, opt, description, callback, dep)            \
    extern void (callback)();                                                 \
    static CallbackCommand callback##name(opt, description, dep, callback);

class Command
{
    Command(const Command&) = delete;
    Command operator=(const Command&) = delete;

    public:
        static Command& instance();

        const std::list<BasicCommand*> registered_cmd_get() const;
        void enable_cmd(BasicCommand* cmd);
        void enable_cmd(const std::string& cmd);
        bool is_enable(const std::string& cmd) const;

        void register_command(BasicCommand* cmd);
        void parse_cmd(int argc, char *argv[]);

        void run();

    private:
        Command();
        ~Command();

    private:
        std::list<BasicCommand*> registered_cmd_;
        std::list<BasicCommand*> enabled_cmd_;
};

#endif /* !COMMAND_HH */
