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

#ifndef CALLBACK_COMMAND_HH
# define CALLBACK_COMMAND_HH

# include <command/basic-command.hh>

namespace command
{
    typedef void (*CallbackHandler)();

    class CallbackCommand : public BasicCommand
    {
        public:
            CallbackCommand(const std::string& opt,
                            const std::string& description,
                            const std::string& dependancies,
                            CallbackHandler handler);
            virtual ~CallbackCommand();

            virtual void run() override;

        private:
            CallbackHandler handler_;
    };
} // namespace command

#endif /* !CALLBACK_COMMAND_HH */
