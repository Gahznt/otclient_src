/*
 * Copyright (c) 2010-2014 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <framework/core/application.h>
#include <framework/core/resourcemanager.h>
#include <framework/luaengine/luainterface.h>
#include <client/client.h>

int main(int argc, const char* argv[])
{
    std::vector<std::string> args(argv, argv + argc);

	// setup application name and version
    g_app.setName("For The Throne Battle");
    g_app.setCompactName("FTB");
    g_app.setVersion(VERSION);

	if (FindWindow("FTB", NULL) > 0 && (args.size() != 3 || args.at(1).compare("stdlib") != 0)) {
		g_logger.fatal("There is already a opened For The Throne Battle client.");
		return 0;
	}
	/*
	if (args.size() != 3) {
		g_logger.fatal("The client is outdated. Please run the game through the launcher!");
		return 0;
	}

	if (args.at(1).compare("stdlib") != 0 && FindWindow("WOP", NULL) > 0) {
		g_logger.fatal("There is already a opened World Of Piece client.");
		return 0;
	}

	if (args.at(2).compare("stdforminput") != 0) {
		g_logger.fatal("Something went wrong. Please run the game through the launcher!");
		return 0;
	}
	*/

	// initialize application framework and otclient
    g_app.init(args);
    g_client.init(args);

    // find script init.lua and run it
    if(!g_resources.discoverWorkDir("init.lua"))
        g_logger.fatal("Unable to find work directory, the application cannot be initialized.");

    if(!g_lua.safeRunScript("init.lua"))
        g_logger.fatal("Unable to run script init.lua!");

    // the run application main loop
    g_app.run();

    // unload modules
    g_app.deinit();

    // terminate everything and free memory
    g_client.terminate();
    g_app.terminate();
    return 0;
}
