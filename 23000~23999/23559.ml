open! Core
(* open! StdLabels *)

let () =
  match In_channel.input_lines In_channel.stdin |> List.map ~f:(String.split ~on:' ') with
  | [ _; x ] :: menu ->
    let pq, base =
      List.fold menu ~init:(Int.Map.empty, 0) ~f:(fun (pq, base) menu ->
        match List.map menu ~f:Int.of_string with
        | [ p; q ] ->
          let diff = p - q in
          if diff > 0 then Map.add_multi pq ~key:diff ~data:(), base + q else pq, base + q
        | _ -> assert false)
    in
    let budget = Int.of_string x - (List.length menu * 1000) in
    let rec loop pq budget acc =
      if budget < 4000
      then acc
      else (
        match Map.max_elt pq with
        | None -> acc
        | Some (diff, cnt) ->
          let cnt = Int.min (List.length cnt) (budget / 4000) in
          let budget = budget - (cnt * 4000) in
          let acc = acc + (diff * cnt) in
          loop (Map.remove pq diff) budget acc)
    in
    loop pq budget base |> Int.to_string |> Out_channel.output_string Out_channel.stdout
  | _ -> ()
;;
