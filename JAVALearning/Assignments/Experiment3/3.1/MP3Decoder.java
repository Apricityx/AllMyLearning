public class MP3Decoder implements Decoder{
    public boolean canDecode(String path) {
        return path.endsWith(".mp3");
    }
    public String decode(String path) {
        return "MP3";
    }
}
