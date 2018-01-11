external console_print : string -> unit = "console_print"
external set_board_led : bool -> unit = "set_board_led"
external sleep : int -> unit = "sleep_ml"

let () = console_print "hello world from ocaml!"

let () = while true do
    set_board_led true;
    sleep 1;
    set_board_led false;
    sleep 1;
done;;


