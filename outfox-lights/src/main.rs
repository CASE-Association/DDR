use std::str::FromStr;
use std::thread;
use std::{thread::sleep, time::Duration};
use std::net::{UdpSocket, SocketAddr};

use toy_arms::external::{read, Process};

// This program presses keys for the Arduino and fetches lights from the DDR clone

fn main(){
    println!("connecting to outfox");
    loop{
        let err = outfox_routine();

        println!("Outfox routine error: {err}");
        thread::sleep(Duration::from_secs(3));
    }
}

fn outfox_routine() -> String{
    let Ok(of) = Process::from_process_name("OutFox.exe") else{
        return "Outfox process not found".to_string();
    };
    let h = of.process_handle;
    let Ok(base) = of.get_module_base("OutFox.exe")else{
        return "Outfox base not found".to_string();
    };
    let addr = base + 0x1BE37F0;


    let address = SocketAddr::from_str("127.0.0.1:6969").unwrap();
    let socket = UdpSocket::bind("127.0.0.1:5433").unwrap();

    println!("Connected!");

    loop{
        if let Ok(vals) = (0..6).map(|x| read(h, addr + x)).collect::<Result<Vec<u8>, _>>(){
            socket.send_to(&vals, address).unwrap();
        }else{
            return "Outfox read error".to_string();
        }
        sleep(Duration::from_millis(20));

    }
}

// !cargo r --release
