
/*
 @author luis ortiz, @author ivan garcia
*/
import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class ClienteJ {
    public static void main(String[] args) {
        String serverName = "localhost"; // Cambiar por el nombre o IP del servidor si es necesario
        int port = 5604;
        Scanner reader = new Scanner(System.in);
        int number;
        char[] buffer = new char[1024];
        try (
            Socket clientSocket = new Socket(serverName, port);
            OutputStreamWriter out = new OutputStreamWriter(clientSocket.getOutputStream(), "UTF-8");) {
                do { 
                    System.out.println("Para salir introduzca 0");
                    System.out.println("Por favor introduzca un número: ");
            number = reader.nextInt(); //leemos el numero del usuario
            out.write(Integer.toString(number));//lo enviamos
            out.flush();
            System.out.println("Número enviado: " + number);

            InputStream inputStream = clientSocket.getInputStream();
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream, StandardCharsets.UTF_8);

            int bytesRead = inputStreamReader.read(buffer);//leemos lo del server
            String mensaje = new String(buffer, 0, bytesRead);

            int numero = Integer.parseInt(mensaje);     //convertimos a entero
            System.out.println("El número recibido es: " + numero);
        } while (number != 0);
            clientSocket.close();

        } catch (UnknownHostException e) {
            System.err.println("Host desconocido: " + serverName);
            e.printStackTrace();
        } catch (IOException e) {
            System.err.println("Error al conectarse al servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
