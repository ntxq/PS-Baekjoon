(* open! Core *)
open! StdLabels

let rec dfs u adj visited order =
  visited.(u) <- true;
  List.iter adj.(u) ~f:(fun v -> if not visited.(v) then dfs v adj visited order);
  Queue.push u order
;;

let topological_sort adj =
  let visited = Array.make (Array.length adj) false in
  let order = Queue.create () in
  for u = 0 to Array.length adj - 1 do
    if not visited.(u) then dfs u adj visited order
  done;
  Queue.to_seq order |> List.of_seq |> List.rev
;;

let filter_order targets adj_rev order =
  let is_required = Array.make (Array.length adj_rev) false in
  let rec loop u =
    is_required.(u) <- true;
    List.iter adj_rev.(u) ~f:(fun v -> if not is_required.(v) then loop v)
  in
  List.iter targets ~f:loop;
  List.filter order ~f:(fun u -> is_required.(u))
;;

let handle_case case_idx =
  let m = input_line stdin |> int_of_string in
  let names = Hashtbl.create m in
  let idexes = Hashtbl.create m in
  let get_idx name =
    if Hashtbl.mem names name
    then Hashtbl.find names name
    else (
      let idx = Hashtbl.length names in
      Hashtbl.add names name idx;
      Hashtbl.add idexes idx name;
      idx)
  in
  let adj = Array.make 301 [] in
  let adj_rev = Array.make 301 [] in
  for _ = 1 to m do
    match input_line stdin |> String.split_on_char ~sep:':' with
    | [ u; v ] ->
      let u_idx = get_idx u in
      let v_idx = get_idx v in
      adj.(v_idx) <- u_idx :: adj.(v_idx);
      adj_rev.(u_idx) <- v_idx :: adj_rev.(u_idx)
    | _ -> assert false
  done;
  let q = input_line stdin |> int_of_string in
  let rec loop idx acc =
    if idx = q
    then acc
    else (
      let target = input_line stdin |> get_idx in
      loop (idx + 1) (target :: acc))
  in
  let targets = loop 0 [] in
  let order = topological_sort adj |> filter_order targets adj_rev in
  String.concat
    [ "Case #"
    ; string_of_int (case_idx + 1)
    ; ": "
    ; string_of_int (List.length order)
    ; "\n"
    ]
    ~sep:""
  |> output_string stdout;
  List.iter order ~f:(fun u ->
    Hashtbl.find idexes u |> output_string stdout;
    output_char stdout '\n')
;;

let () =
  let t = input_line stdin |> int_of_string in
  for i = 0 to t - 1 do
    handle_case i
  done
;;
