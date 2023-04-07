open! StdLabels
open! MoreLabels

let rec gcd a b = Int64.(if equal b zero then a else gcd b (rem a b))
let lcm a b = Int64.(div (mul a b) (gcd a b))
let () = Scanf.scanf "%Ld %Ld" (fun a b -> lcm a b) |> Printf.printf "%Ld\n"
