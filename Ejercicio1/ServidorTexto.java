/*
 @author luis ortiz, @author ivan garcia
*/

// Paquetes para la comunicacion de red y E/S
import java.net.*; // Comunicacion de red
import java.io.*; // Comunicacion E/S
import java.nio.charset.StandardCharsets;

public class ServidorTexto {

    public static void main(String[] args) throws IOException {
        // Declaracion de un ServerSocket para recibir conexiones
        ServerSocket serverSocket = null;
        try {
            // El socket se abre en el puerto 6000
            serverSocket = new ServerSocket(6000);
            System.out.println("Servidor en el puerto 6000");
        } catch (IOException e) {
            System.err.println("No puedo escuchar el puerto: 6000");
            System.exit(1);
        }

        Socket clientSocket = null;
        try {
            System.out.println("Esperando conexión...");
            // Acepta la peticion de conexion
            clientSocket = serverSocket.accept();
            System.out.println("Conexión exitosa con cliente(:");
        } catch (IOException e) {
            System.err.println("Fallo para aceptar la conexión.");
            System.exit(1);
        }

        // Enviar mensajes al cliente
        OutputStream outputStream = clientSocket.getOutputStream();
        OutputStreamWriter outputStreamWriter = new OutputStreamWriter(outputStream, StandardCharsets.UTF_8);//usando formato utf8
        String mensaje2 = "Hola desde Java";
        outputStreamWriter.write(mensaje2);
        outputStreamWriter.flush();
        
        // Leer los mensajes del cliente
        InputStream inputStream = clientSocket.getInputStream();
        InputStreamReader inputStreamReader = new InputStreamReader(inputStream, StandardCharsets.UTF_8);
        char[] buffer = new char[1024];
        int bytesRead = inputStreamReader.read(buffer);
        String mensaje = new String(buffer, 0, bytesRead);
        System.out.println("El mensaje recibido es: " + mensaje);
 
    
        clientSocket.close();
        serverSocket.close();
    }
}
