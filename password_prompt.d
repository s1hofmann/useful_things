import std.process;
import std.stdio;
import std.string;

int main()
{
    string password;
	executeShell("stty -echo");
	password = chomp(readln());
	executeShell("stty echo");
    
    writeln("Password: ", password);

    return 0;
}
