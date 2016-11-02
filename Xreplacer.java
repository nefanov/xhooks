public class Xreplacer
{
	public native int change_table(String[] old, String[] curr, int len);

	static {
		System.load("libxrep.so");
	}
}
