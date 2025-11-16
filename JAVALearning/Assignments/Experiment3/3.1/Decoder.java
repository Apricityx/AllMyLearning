public interface Decoder {
    boolean canDecode(String path);
    String decode(String path);
}
