open! StdLabels
open! MoreLabels

let get_win_rate =
  let dp = Hashtbl.create 100000 in
  let rec get_win_rate n m k =
    if n = 0
    then 0.0
    else if k = 0
    then 1.0
    else (
      match Hashtbl.find_opt dp (n, m, k) with
      | Some v -> v
      | None ->
        let up_coin = (n / m) + 1 in
        let up_count = n mod m in
        let up_win_rate =
          get_win_rate (n - up_coin) m (k - 1) *. (float_of_int up_count /. float_of_int m)
        in
        let down_coin = n / m in
        let down_count = m - up_count in
        let down_win_rate =
          get_win_rate (n - down_coin) m (k - 1)
          *. (float_of_int down_count /. float_of_int m)
        in
        let win_rate = up_win_rate +. down_win_rate in
        Hashtbl.add dp ~key:(n, m, k) ~data:win_rate;
        win_rate)
  in
  get_win_rate
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; k ] ->
    get_win_rate n m k |> Printf.sprintf "%.5f" |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
